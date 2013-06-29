#include <mu/llvmc/generator.hpp>

#include <inttypes.h>

#include <mu/llvmc/ast.hpp>
#include <mu/core/error_string.hpp>
#include <mu/llvmc/skeleton.hpp>
#include <mu/llvmc/skeleton_t.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>
#include <llvm/InlineAsm.h>
#include <llvm/Support/Dwarf.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/DebugLoc.h>

#include <boost/array.hpp>

#include <gc_cpp.h>

#include <algorithm>

#include <stdlib.h>

#include <stdio.h>

mu::llvmc::generator_result mu::llvmc::generator::generate (llvm::LLVMContext & context_a, mu::llvmc::skeleton::module * module_a, mu::string const & name_a, mu::string const & path_a, uint64_t module_id_a)
{
	char id [32];
	sprintf (id, "%016" PRIx64 "", module_id_a);
    mu::llvmc::generator_result result;
    result.module = new llvm::Module (id, context_a);
    mu::llvmc::generate_module generator (module_a, result, name_a, path_a, module_id_a);
    generator.generate ();
    return result;
}

mu::llvmc::generate_module::generate_module (mu::llvmc::skeleton::module * module_a, mu::llvmc::generator_result & target_a, mu::string const & name_a, mu::string const & path_a, uint64_t module_id_a) :
builder (*target_a.module),
module (module_a),
target (target_a),
module_id (module_id_a)
{
	builder.createCompileUnit (llvm::dwarf::DW_LANG_C, std::string (name_a.begin (), name_a.end ()), std::string (path_a.begin (), path_a.end ()), "MU 0 (Colin LeMahieu)", false, "", 0);
    file = builder.createFile (std::string (name_a.begin (), name_a.end ()), std::string (path_a.begin (), path_a.end ()));
}

void mu::llvmc::generate_module::generate ()
{
    for (auto i (module->globals.begin ()), j (module->globals.end ()); i != j; ++i)
    {
		assert (i->second->generated == nullptr);
		auto function (dynamic_cast <mu::llvmc::skeleton::function *> (i->second));
        if (function != nullptr)
        {
            auto type (&function->type_m);
            retrieve_type (type);
            auto function_type (llvm::cast <llvm::FunctionType> (type->generated));
            auto function_l (llvm::Function::Create (function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage));
            target.module->getFunctionList ().push_back (function_l);
            i->second->generated = function_l;
            i->second->predicate = llvm::ConstantInt::getTrue (function_type->getContext ());
            target.names [i->first] = function_l;
        }
        else
        {
            generate_value (i->second);
        }
	}
	uint64_t global_id (0);
    for (auto i (module->globals.begin ()), j (module->globals.end ()); i != j; ++i, ++global_id)
    {
        assert (i->second->predicate != nullptr);
        if (i->second->generated != nullptr)
        {
            std::string name;
            char buffer [32];
            sprintf (buffer, "%016" PRIx64, module_id);
            name.append (buffer);
            name.push_back ('-');
            sprintf (buffer, "%016" PRIx64, global_id);
            name.append (buffer);
            name.push_back ('-');
            name += std::string (i->first.begin (), i->first.end ());
            i->second->generated->setName (name);
        }
        else
        {
            // unit
        }
		auto function_l (dynamic_cast <mu::llvmc::skeleton::function *> (i->second));
        if (function_l != nullptr)
        {
            auto function (llvm::cast <llvm::Function> (i->second->generated));
            assert (function->getBasicBlockList().empty ());
            mu::llvmc::generate_function generator_l (*this, function_l);
            generator_l.generate ();
        }
        else
        {
            auto global_variable (dynamic_cast <mu::llvmc::skeleton::global_variable *> (i->second));
            if (global_variable != nullptr)
            {
                builder.createGlobalVariable (std::string (i->first.begin (), i->first.end ()), file, global_variable->region.first.row, global_variable->type ()->debug, false, global_variable->generated);
            }
            // Only generate function bodies second pass
        }
    }
	builder.finalize ();
}

mu::llvmc::generate_function::generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a) :
module (module_a),
function (function_a),
function_return_type (function_a->get_return_type ())
{
}

static std::string strip_unique (std::string const & name_a)
{
    assert (name_a.size () >= 34);
    std::string result (name_a.begin () + 34, name_a.end ());
    return result;
}

void mu::llvmc::generate_function::generate ()
{
    auto & context (module.target.module->getContext ());
    assert (function->predicate != nullptr);
    auto function_l (llvm::cast <llvm::Function> (function->generated));
    auto type (&function->type_m);
    module.retrieve_type (type);
    auto function_type (llvm::cast <llvm::FunctionType> (type->generated));
	function_d = module.builder.createFunction (module.file, strip_unique (function_l->getName ()), function_l->getName (), module.file, function->region.first.row, type->debug, false, true, function->region.first.row, 0, false, function_l);
    block_d = module.builder.createLexicalBlock (function_d, module.file, function->region.first.row, function->region.first.column);
    function_m = function_l;
    auto entry (llvm::BasicBlock::Create (context));
    last = entry;
    function_l->getBasicBlockList ().push_back (entry);
    {
        auto i (function_l->arg_begin());
        auto j (function_l->arg_end());
        auto k (function->parameters.begin ());
        auto l (function->parameters.end ());
        for (; i != j; ++i, ++k)
        {
            auto value (*k);
            assert (k != l);
            llvm::Value * parameter (i);
            value->generated = parameter;
            value->predicate = llvm::ConstantInt::getTrue (context);
            auto existing (value->type ());
            assert (existing->generated != nullptr);
            auto const & name ((*k)->name);
            module.builder.insertDeclare (parameter, module.builder.createLocalVariable (llvm::dwarf::DW_TAG_arg_variable, function_d, std::string (name.begin (), name.end ()), module.file, 0, existing->debug), entry);
        }
        assert ((i != j) == (k != l));
    }
    switch (function_return_type)
    {
        case mu::llvmc::skeleton::function_return_type::b0:
        {
            auto ret (new llvm::UnreachableInst (function_l->getContext ()));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function_d));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1v0:
        {
            function->for_each_results (
                [&]
                (mu::llvmc::skeleton::result * result_a, size_t)
                {
                    retrieve_value (result_a->value);
                    assert (result_a->type->is_unit_type ());
                },
                [&]
                (mu::llvmc::skeleton::value * value_a, size_t)
                {
                    retrieve_value (value_a);
                }
            );
            auto ret (llvm::ReturnInst::Create (function_l->getContext ()));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function_d));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1v1:
        {
            llvm::Value * the_value (nullptr);
            function->for_each_results (
                [&]
                (mu::llvmc::skeleton::result * result_a, size_t)
                {
                    retrieve_value (result_a->value);
                    assert (the_value == nullptr || result_a->type->is_unit_type ());
                    the_value = result_a->type->is_unit_type () ? the_value : result_a->value->generated;
                },
                [&]
                (mu::llvmc::skeleton::value * value_a, size_t)
                {
                    retrieve_value (value_a);
                }
            );
            auto ret (llvm::ReturnInst::Create (function_l->getContext (), the_value));            
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function_d));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1vm:
        {
            assert (function->branch_ends.size () == 1);
            assert (function->branch_ends [0] == function->results.size ());
            llvm::Value * result (llvm::UndefValue::get (function_type->getReturnType ()));
            unsigned index (0);
            function->for_each_results (
                [&]
                (mu::llvmc::skeleton::result * result_a, size_t)
                {
                    retrieve_value (result_a->value);
                    if (!result_a->type->is_unit_type ())
                    {
                        auto insert = llvm::InsertValueInst::Create (result, result_a->value->generated, llvm::ArrayRef <unsigned> (index));
                        last->getInstList ().push_back (insert);
                        result = insert;
                        ++index;
                    }
                },
                [&]
                (mu::llvmc::skeleton::value * value_a, size_t)
                {
                    retrieve_value (value_a);
                }
            );
            auto ret (llvm::ReturnInst::Create (function_l->getContext (), result));            
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function_d));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::bmv0:
        {
            auto results (generate_result_set ());
            assert (results.size () == 1);
            auto ret (llvm::ReturnInst::Create (function_l->getContext (), results [0]));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function_d));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::bmvm:
        {
            auto results (generate_result_set ());
            assert (results.size () > 1);
            llvm::Value * result (llvm::UndefValue::get (function_type->getReturnType ()));
            unsigned int index (0);
            for (auto i: results)
            {
                auto instruction (llvm::InsertValueInst::Create (result, i, llvm::ArrayRef <unsigned int> (index)));
                last->getInstList().push_back (instruction);
                result = instruction;
                ++index;
            }
            auto ret (llvm::ReturnInst::Create (function_l->getContext (), result));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function_d));
            last->getInstList ().push_back (ret);
            break;
        }
        default:
            assert (false);
    }
}

std::vector <llvm::Value *> mu::llvmc::generate_function::generate_result_set ()
{
    std::vector <llvm::Value *> result;
    auto & context (function_m->getContext ());
    auto type (llvm::Type::getInt8Ty (context));
    llvm::Value * selector (llvm::UndefValue::get (type));
    llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
    uint8_t selector_number (0);
    function->for_each_results (
        [&]
        (mu::llvmc::skeleton::result * result_a, size_t)
        {
            retrieve_value (result_a->value);
            if (!result_a->type->is_unit_type())
            {
                result.push_back (result_a->value->generated);
            }
            auto instruction (llvm::BinaryOperator::CreateAnd (predicate, result_a->value->predicate));
            last->getInstList ().push_back (instruction);
            predicate = instruction;
        },
        [&]
        (mu::llvmc::skeleton::value * value_a, size_t)
        {
            retrieve_value (value_a);
        },
        mu::llvmc::skeleton::function::empty_node,
        [&]
        (mu::llvmc::skeleton::node * node_a, size_t)
        {
            auto selector_new (llvm::SelectInst::Create (predicate, llvm::ConstantInt::get (type, selector_number), selector));
            last->getInstList().push_back (selector_new);
            selector = selector_new;
            predicate = llvm::ConstantInt::getTrue (context);
            ++selector_number;
        }
    );
    result.push_back (selector);
    return result;
}

namespace mu
{
    namespace llvmc
    {
        class generate_value : public mu::llvmc::skeleton::visitor
        {
        public:
            generate_value (mu::llvmc::generate_function & function_a) :
            function_m (function_a)
            {
            }
            mu::llvmc::generate_function & function_m;
            void value (mu::llvmc::skeleton::value * value_a) override
            {
                function_m.module.generate_global (value_a, [=] (mu::llvmc::skeleton::value * value_a) {function_m.retrieve_value (value_a);});
            }
            void call_element (mu::llvmc::skeleton::call_element * node_a) override
            {
                auto call_a (node_a->source);
                auto & context (function_m.module.target.module->getContext ());
                llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
                assert (call_a->arguments.size () > 0);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (call_a->arguments [0]) != nullptr);
                assert (call_a->target->predicate != nullptr);
                auto function (call_a->target->generated);
                std::vector <llvm::Value *> arguments;
                size_t position (1);
                auto end (call_a->predicate_offset);
                for (auto i (call_a->arguments.begin () + 1); position < end; ++i, ++position)
                {
                    auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
                    function_m.retrieve_value (value);
                    auto instruction (llvm::BinaryOperator::CreateAnd (predicate, value->predicate));
                    function_m.last->getInstList ().push_back (instruction);
                    predicate = instruction;
                    assert (value->predicate != nullptr);
                    arguments.push_back (value->generated);
                }
                predicate = function_m.process_predicates (predicate, call_a->arguments, position);
                auto call_block (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (call_block);
                auto new_last (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (new_last);
                auto return_type (call_a->target->get_return_type ());
                switch (return_type)
                {
                    case mu::llvmc::skeleton::function_return_type::b0:
                    {
                        auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                        assert (call_a->elements.size () == 1);
                        call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, function_m.block_d));
                        call_block->getInstList ().push_back (call_l);
                        call_a->elements [0]->generated = nullptr;
                        call_a->elements [0]->predicate = predicate;
                        break;
                    }
                    case mu::llvmc::skeleton::function_return_type::b1v0:
                    {
                        auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                        assert (call_a->elements.size () == 1);
                        call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, function_m.block_d));
                        call_block->getInstList ().push_back (call_l);
                        call_a->elements [0]->generated = nullptr;
                        call_a->elements [0]->predicate = predicate;
                        break;
                    }
                    case mu::llvmc::skeleton::function_return_type::b1v1:
                    {
                        auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                        assert (call_a->elements.size () == 1);
                        call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, function_m.block_d));
                        call_block->getInstList ().push_back (call_l);
                        auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
                        new_last->getInstList ().push_back (real_call);
                        real_call->addIncoming (call_l, call_block);
                        real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), function_m.last);
                        call_a->elements [0]->generated = real_call;
                        call_a->elements [0]->predicate = predicate;
                        break;
                    }
                    case mu::llvmc::skeleton::function_return_type::b1vm:
                    {
                        auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                        assert (call_a->elements.size () > 0);
                        call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, function_m.block_d));
                        call_block->getInstList ().push_back (call_l);
                        unsigned position (0);
                        auto k (call_a->elements.begin ());
                        auto l (call_a->elements.end ());
                        call_a->target->for_each_results (
                                                          [&]
                                                          (mu::llvmc::skeleton::result * result_a, size_t)
                                                          {
                                                              auto element (llvm::ExtractValueInst::Create (call_l, position));
                                                              call_block->getInstList ().push_back (element);
                                                              auto real_element (llvm::PHINode::Create (element->getType (), 2));
                                                              new_last->getInstList ().push_back (real_element);
                                                              real_element->addIncoming (element, call_block);
                                                              real_element->addIncoming (llvm::UndefValue::get (element->getType ()), function_m.last);
                                                              auto value (*k);
                                                              value->generated = real_element;
                                                              value->predicate = predicate;
                                                              ++k;
                                                              ++position;
                                                          }
                                                          );
                        assert (k == l);
                        break;
                    }
                    case mu::llvmc::skeleton::function_return_type::bmv0:
                    {
                        auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                        assert (call_a->elements.size () > 0);
                        call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, function_m.block_d));
                        call_block->getInstList ().push_back (call_l);
                        auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
                        new_last->getInstList ().push_back (real_call);
                        real_call->addIncoming (call_l, call_block);
                        real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), function_m.last);
                        unsigned position (0);
                        auto selector_type (llvm::Type::getInt8Ty (context));
                        auto k (call_a->elements.begin ());
                        auto l (call_a->elements.end ());
                        call_a->target->for_each_results (
                                                          [&]
                                                          (mu::llvmc::skeleton::result *, size_t)
                                                          {
                                                              auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, real_call, llvm::ConstantInt::get (selector_type, position)));
                                                              new_last->getInstList ().push_back (compare);
                                                              auto instruction (llvm::BinaryOperator::CreateAnd (predicate, compare));
                                                              new_last->getInstList ().push_back (instruction);
                                                              auto value (*k);
                                                              value->generated = nullptr;
                                                              value->predicate = instruction;
                                                              ++k;
                                                              ++position;
                                                          }
                                                          );
                        assert (k == l);
                        break;
                    }
                    case mu::llvmc::skeleton::function_return_type::bmvm:
                    {
                        auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                        assert (call_a->elements.size () > 0);
                        call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, function_m.block_d));
                        call_block->getInstList ().push_back (call_l);
                        auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
                        new_last->getInstList ().push_back (real_call);
                        real_call->addIncoming (call_l, call_block);
                        real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), function_m.last);
                        auto function_result (llvm::cast <llvm::StructType> (call_l->getType ()));
                        assert (function_result->getNumElements () > 1);
                        auto selector (llvm::ExtractValueInst::Create (real_call, llvm::ArrayRef <unsigned> (function_result->getNumElements () - 1)));
                        new_last->getInstList ().push_back (selector);
                        auto selector_type (llvm::Type::getInt8Ty (context));
                        auto current_element (call_a->elements.begin ());
                        auto end_element (call_a->elements.end ());
                        size_t current_selector (0);
                        unsigned result_index (0);
                        auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, selector, llvm::ConstantInt::get (selector_type, current_selector)));
                        new_last->getInstList ().push_back (compare);
                        auto instruction (llvm::BinaryOperator::CreateAnd (predicate, compare));
                        new_last->getInstList ().push_back (instruction);
                        call_a->target->for_each_results (
                                                          [&]
                                                          (mu::llvmc::skeleton::result * result_a, size_t)
                                                          {
                                                              assert (current_element != end_element);
                                                              if (!result_a->type->is_unit_type ())
                                                              {
                                                                  auto extraction (llvm::ExtractValueInst::Create (real_call, llvm::ArrayRef <unsigned> (result_index)));
                                                                  new_last->getInstList().push_back (extraction);
                                                                  auto value (*current_element);
                                                                  value->generated = extraction;
                                                                  value->predicate = instruction;
                                                                  ++result_index;
                                                                  ++current_element;
                                                              }
                                                              else
                                                              {
                                                                  auto value (*current_element);
                                                                  value->generated = nullptr;
                                                                  value->predicate = instruction;
                                                              }
                                                          },
                                                          mu::llvmc::skeleton::function::empty_node,
                                                          mu::llvmc::skeleton::function::empty_node,
                                                          [&]
                                                          (mu::llvmc::skeleton::node * result_a, size_t)
                                                          {
                                                              ++current_selector;
                                                              compare = new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, selector, llvm::ConstantInt::get (selector_type, current_selector));
                                                              new_last->getInstList ().push_back (compare);
                                                              instruction = llvm::BinaryOperator::CreateAnd (predicate, compare);
                                                              new_last->getInstList ().push_back (instruction);
                                                          }
                                                          );
                        assert (current_element == end_element);
                        break;
                    }
                    default:
                        assert (false);
                        break;
                }
                auto join_branch (llvm::BranchInst::Create (new_last));
                call_block->getInstList ().push_back (join_branch);
                auto call_branch (llvm::BranchInst::Create (call_block, new_last, predicate));
                function_m.last->getInstList ().push_back (call_branch);
                function_m.last = new_last;
            }
            void switch_element (mu::llvmc::skeleton::switch_element * element) override
            {
                assert (element->source->arguments.size () > 1);
                llvm::Value * predicate (llvm::ConstantInt::getTrue (function_m.last->getContext ()));
                auto arg1 (mu::cast <mu::llvmc::skeleton::value> (element->source->arguments [1]));
                function_m.retrieve_value (arg1);
                auto instruction (llvm::BinaryOperator::CreateAnd (predicate, arg1->predicate));
                function_m.last->getInstList ().push_back (instruction);
                predicate = instruction;
                auto & elements (element->source->elements);
                size_t position (0);
                for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i, ++position)
                {
                    auto value (*i);
                    auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, arg1->generated, llvm::ConstantInt::get (arg1->generated->getType (), value->value_m->value_m)));
                    function_m.last->getInstList().push_back (compare);
                    auto switch_predicate (llvm::BinaryOperator::CreateAnd (predicate, compare));
                    function_m.last->getInstList().push_back (switch_predicate);
                    value->generated = nullptr;
                    value->predicate = switch_predicate;
                }
                predicate = function_m.process_predicates (predicate, element->source->arguments, position);
            }
            void loop_element (mu::llvmc::skeleton::loop_element * loop_element) override
            {
                auto & context (function_m.module.target.module->getContext ());
                llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
                std::vector <llvm::PHINode *> parameters;
                auto loop_entry (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (loop_entry);
                {
                    size_t position (0);
                    auto end (loop_element->source->argument_predicate_offset);
                    assert (loop_element->source->arguments.size () >= loop_element->source->argument_predicate_offset);
                    for (auto i (loop_element->source->arguments.begin ()); position < end; ++i, ++position)
                    {
                        assert (i != loop_element->source->arguments.end ());
                        auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
                        function_m.retrieve_value (value);
                        predicate = function_m.and_predicates (predicate, value->predicate);
                        auto loop_parameter (llvm::PHINode::Create (value->generated->getType (), 2));
                        loop_parameter->addIncoming (value->generated, function_m.last);
                        loop_entry->getInstList ().push_back (loop_parameter);
                        assert (position < loop_element->source->parameters.size ());
                        loop_element->source->parameters [position]->generated = loop_parameter;
                        loop_element->source->parameters [position]->predicate = predicate;
                        parameters.push_back (loop_parameter);
                    }
                    assert (position == loop_element->source->parameters.size ());
                }
                auto entry (function_m.last);
                auto successor (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (successor);
                entry->getInstList ().push_back (llvm::BranchInst::Create (loop_entry, successor, predicate));
                function_m.last = loop_entry;
                auto feedback_branch (true);
                auto branch_predicate (predicate);
                llvm::Value * feedback_predicate;
                size_t parameter_position (0);
                size_t element_position (0);
                auto empty (true);
                loop_element->source->for_each_results (
                                                        [&]
                                                        (mu::llvmc::skeleton::node * node_a, size_t)
                                                        {
                                                            empty = false;
                                                            auto value (mu::cast <mu::llvmc::skeleton::value> (node_a));
                                                            function_m.retrieve_value (value);
                                                            branch_predicate = function_m.and_predicates (branch_predicate, value->predicate);
                                                            if (feedback_branch)
                                                            {
                                                                assert (parameter_position < parameters.size ());
                                                                parameters [parameter_position]->addIncoming (value->generated, function_m.last);
                                                                ++parameter_position;
                                                            }
                                                            else
                                                            {
                                                                auto real_value (llvm::PHINode::Create (value->generated->getType (), 2));
                                                                real_value->addIncoming (llvm::UndefValue::get (value->generated->getType ()), function_m.last);
                                                                real_value->addIncoming (value->generated, function_m.last);
                                                                successor->getInstList ().push_back (real_value);
                                                                parameters.push_back (real_value);
                                                                auto real_predicate (llvm::PHINode::Create (value->predicate->getType (), 2));
                                                                real_predicate->addIncoming (llvm::UndefValue::get (value->predicate->getType ()), function_m.last);
                                                                real_predicate->addIncoming (value->predicate, function_m.last);
                                                                successor->getInstList ().push_back (real_predicate);
                                                                parameters.push_back (real_predicate);
                                                                assert (element_position < loop_element->source->elements.size ());
                                                                loop_element->source->elements [element_position]->generated = real_value;
                                                                loop_element->source->elements [element_position]->predicate = real_predicate;
                                                                ++element_position;
                                                            }
                                                        },
                                                        [&]
                                                        (mu::llvmc::skeleton::node * node_a, size_t)
                                                        {
                                                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (node_a));
                                                            auto value (static_cast <mu::llvmc::skeleton::value *> (node_a));
                                                            function_m.retrieve_value (value);
                                                            branch_predicate = function_m.and_predicates (branch_predicate, value->predicate);
                                                        },
                                                        mu::llvmc::skeleton::loop::empty_node,
                                                        [&]
                                                        (mu::llvmc::skeleton::node * node_a, size_t)
                                                        {
                                                            if (feedback_branch)
                                                            {
                                                                feedback_predicate = branch_predicate;
                                                                feedback_branch = false;
                                                            }
                                                            if (empty)
                                                            {
                                                                auto real_predicate (llvm::PHINode::Create (branch_predicate->getType (), 2));
                                                                real_predicate->addIncoming (llvm::UndefValue::get (branch_predicate->getType ()), function_m.last);
                                                                real_predicate->addIncoming (branch_predicate, function_m.last);
                                                                successor->getInstList ().push_back (real_predicate);
                                                                parameters.push_back (real_predicate);
                                                                assert (element_position < loop_element->source->elements.size ());
                                                                loop_element->source->elements [element_position]->generated = nullptr;
                                                                loop_element->source->elements [element_position]->predicate = real_predicate;
                                                                ++element_position;
                                                            }
                                                            empty = true;
                                                            branch_predicate = predicate;
                                                        }
                                                        );
                for (auto i: parameters)
                {
                    i->setIncomingBlock (0, entry);
                    i->setIncomingBlock (1, function_m.last);
                }
                auto feedback (llvm::BranchInst::Create (loop_entry, successor, feedback_predicate));
                function_m.last->getInstList ().push_back (feedback);
                function_m.last = successor;
            }
            void identity_element_value (mu::llvmc::skeleton::identity_element_value * identity_value) override
            {
                auto i (identity_value->source->arguments.begin () + 1);
                auto j (identity_value->source->arguments.begin () + identity_value->source->predicate_offset);
                auto k (identity_value->source->elements.begin ());
                auto l (identity_value->source->elements.end ());
                for (; i != j; ++i, ++k)
                {
                    assert (k != l);
                    auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
                    function_m.retrieve_value (value);
                    auto target (*k);
                    target->predicate = value->predicate;
                    target->generated = value->generated;
                }
                assert ((i == j) == (k == l));
                auto m (identity_value->source->arguments.end ());
                for (; i != m; ++i)
                {
                    auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
                    function_m.retrieve_value (value);
                }
            }
            void constant_aggregate_zero (mu::llvmc::skeleton::constant_aggregate_zero * node_a) override
            {
                auto type (node_a->type ());
                function_m.module.retrieve_type (type);
                node_a->predicate = llvm::ConstantInt::getTrue (function_m.module.target.module->getContext ());
                node_a->generated = llvm::ConstantAggregateZero::get (type->generated);
            }
            void join_value (mu::llvmc::skeleton::join_value * join) override
            {
                assert (join->arguments.size () > 1);
                auto unit (join->arguments [0]->type ()->is_unit_type ());
                llvm::Value * predicate (llvm::ConstantInt::getFalse (function_m.function_m->getContext ()));
                auto first (mu::cast <mu::llvmc::skeleton::value> (join->arguments [0]));
                function_m.retrieve_value (first);
                assert (unit == (first->generated == nullptr));
                llvm::Value * value;
                if (!unit)
                {
                    value = llvm::UndefValue::get (first->generated->getType ());
                }
                else
                {
                    value = nullptr;
                }
                for (auto i: join->arguments)
                {
                    auto value_l (mu::cast <mu::llvmc::skeleton::value> (i));
                    function_m.retrieve_value (value_l);
                    auto predicate_instruction (llvm::BinaryOperator::CreateOr (predicate, value_l->predicate));
                    function_m.last->getInstList ().push_back (predicate_instruction);
                    if (!unit)
                    {
                        auto select_instruction (llvm::SelectInst::Create (value_l->predicate, value_l->generated, value));
                        function_m.last->getInstList ().push_back (select_instruction);
                        value = select_instruction;
                    }
                    predicate = predicate_instruction;
                }
                join->predicate = predicate;
                join->generated = value;
            }
            void unit_value (mu::llvmc::skeleton::unit_value * node_a) override
            {
                node_a->generated = nullptr;
                node_a->predicate = llvm::ConstantInt::getTrue (function_m.module.target.module->getContext ());
            }
            void inline_asm (mu::llvmc::skeleton::inline_asm * asm_l) override
            {
                assert (asm_l->arguments.size () > 0);
                assert (dynamic_cast <mu::llvmc::skeleton::asm_c *> (asm_l->arguments [0]) != nullptr);
                auto info (static_cast <mu::llvmc::skeleton::asm_c *> (asm_l->arguments [0]));
                auto end (asm_l->predicate_position);
                auto & context (function_m.module.target.module->getContext ());
                llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
                std::vector <llvm::Type *> types;
                std::vector <llvm::Value *> arguments;
                size_t i (1);
                for (; i < end; ++i)
                {
                    auto value (mu::cast <mu::llvmc::skeleton::value> (asm_l->arguments [i]));
                    function_m.retrieve_value (value);
                    predicate = function_m.and_predicates (predicate, value->predicate);
                    if (value->generated != nullptr)
                    {
                        arguments.push_back (value->generated);
                        types.push_back (value->generated->getType ());
                    }
                }
                for (size_t j (asm_l->arguments.size ()); i < j; ++i)
                {
                    auto value (mu::cast <mu::llvmc::skeleton::value> (asm_l->arguments [i]));
                    function_m.retrieve_value (value);
                    predicate = function_m.and_predicates (predicate, value->predicate);
                }
                llvm::Type * type;
                if (!info->type_m->is_unit_type ())
                {
                    function_m.module.retrieve_type (info->type_m);
                    type = info->type_m->generated;
                }
                else
                {
                    type = llvm::Type::getVoidTy (context);
                }
                auto function_type (llvm::FunctionType::get (type, llvm::ArrayRef <llvm::Type *> (types), false));
                std::string text (info->text.begin (), info->text.end ());
                std::string constraints (info->constraint.begin (), info->constraint.end ());
                auto inline_asm (llvm::InlineAsm::get (function_type, llvm::StringRef (text), llvm::StringRef (constraints), true));
                auto call (llvm::CallInst::Create (inline_asm, arguments));
                auto call_block (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (call_block);
                auto successor (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (successor);
                auto predicate_branch (llvm::BranchInst::Create (call_block, successor, predicate));
                function_m.last->getInstList ().push_back (predicate_branch);
                call_block->getInstList ().push_back (call);
                auto rejoin (llvm::BranchInst::Create (successor));
                call_block->getInstList ().push_back (rejoin);
                llvm::Value * value;
                if (!info->type_m->is_unit_type ())
                {
                    value = function_m.generate_rejoin (function_m.last, call_block, successor, call);
                }
                else
                {
                    value = nullptr;
                }
                asm_l->generated = value;
                asm_l->predicate = predicate;
                function_m.last = successor;
            }
            void named (mu::llvmc::skeleton::named * named) override
            {
                auto value_l (named->value_m);
                function_m.retrieve_value (value_l);
                named->generated = value_l->generated;
                named->predicate = value_l->predicate;
                auto const & name (named->name);
                auto type (named->type ());
                function_m.module.retrieve_type (type);
                assert (type->generated != nullptr);
                if (value_l->generated != nullptr)
                {
                    function_m.module.builder.insertDeclare (value_l->generated, function_m.module.builder.createLocalVariable (llvm::dwarf::DW_TAG_auto_variable, function_m.function_d, std::string (name.begin (), name.end ()), function_m.module.file, named->region.first.row, type->debug), function_m.last);
                }
            }
            void instruction (mu::llvmc::skeleton::instruction * instruction) override
            {
                llvm::Value * predicate;
                llvm::Value * value;
                auto & context (function_m.module.target.module->getContext ());
                switch (instruction->marker ())
                {
                    case mu::llvmc::instruction_type::add:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateAdd (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::and_i:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateAnd (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::alloca:
                    {
                        assert (instruction->predicate_position == 2);
                        assert (dynamic_cast <mu::llvmc::skeleton::type *> (instruction->arguments [1]) != nullptr);
                        auto type (static_cast <mu::llvmc::skeleton::type *> (instruction->arguments [1]));
                        function_m.module.retrieve_type (type);
                        predicate = llvm::ConstantInt::getTrue (function_m.module.target.module->getContext ());
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto predicate_branch (llvm::BasicBlock::Create (context));
                        function_m.function_m->getBasicBlockList().push_back (predicate_branch);
                        auto new_last (llvm::BasicBlock::Create (context));
                        function_m.function_m->getBasicBlockList().push_back (new_last);
                        function_m.last->getInstList ().push_back (llvm::BranchInst::Create (predicate_branch, new_last, predicate));
                        auto instruction_l (new llvm::AllocaInst (type->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        predicate_branch->getInstList ().push_back (instruction_l);
                        predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
                        value = function_m.generate_rejoin (function_m.last, predicate_branch, new_last, instruction_l);
                        function_m.last = new_last;
                        break;
                    }
                    case mu::llvmc::instruction_type::ashr:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateAShr (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::bitcast:
                    {
                        assert (instruction->predicate_position == 3);
                        auto value_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (value_l);
                        auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
                        function_m.module.retrieve_type (type_l);
                        predicate = value_l->predicate;
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BitCastInst::CreatePointerCast (value_l->generated, type_l->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::cmpxchg:
                    {
                        assert (instruction->predicate_position == 4);
                        auto one (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (one);
                        auto two (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (two);
                        auto three (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [3]));
                        function_m.retrieve_value (three);
                        predicate = function_m.and_predicates (one->predicate, two->predicate);
                        predicate = function_m.and_predicates (predicate, three->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto predicate_branch (llvm::BasicBlock::Create (context));
                        function_m.function_m->getBasicBlockList().push_back (predicate_branch);
                        auto new_last (llvm::BasicBlock::Create (context));
                        function_m.function_m->getBasicBlockList().push_back (new_last);
                        function_m.last->getInstList ().push_back (llvm::BranchInst::Create (predicate_branch, new_last, predicate));
                        auto instruction_l (new llvm::AtomicCmpXchgInst (one->generated, two->generated, three->generated, llvm::AtomicOrdering::AcquireRelease, llvm::SynchronizationScope::CrossThread));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        predicate_branch->getInstList ().push_back (instruction_l);
                        predicate_branch->getInstList ().push_back (llvm::BranchInst::Create(new_last));
                        value = function_m.generate_rejoin (function_m.last, predicate_branch, new_last, instruction_l);
                        function_m.last = new_last;
                        break;
                    }
                    case mu::llvmc::instruction_type::getelementptr:
                    {
                        assert (instruction->predicate_position >= 3);
                        auto one (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (one);
                        auto two (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (two);
                        predicate = function_m.and_predicates (one->predicate, two->predicate);
                        std::vector <llvm::Value *> indicies;
                        indicies.push_back (two->generated);
                        for (auto i (instruction->arguments.begin () + 3), j (instruction->arguments.begin () + instruction->predicate_position); i != j; ++i)
                        {
                            auto trailing (mu::cast <mu::llvmc::skeleton::constant_integer> (*i));
                            function_m.retrieve_value (trailing);
                            indicies.push_back (trailing->generated);
                        }
                        predicate = function_m.process_predicates (predicate, instruction->arguments, instruction->predicate_position);
                        auto instruction_l (llvm::GetElementPtrInst::CreateInBounds (one->generated, llvm::ArrayRef <llvm::Value *> (indicies)));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::icmp:
                    {
                        assert (false);
                    }
                    case mu::llvmc::instruction_type::inttoptr:
                    {
                        assert (instruction->predicate_position == 3);
                        auto value_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (value_l);
                        auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
                        function_m.module.retrieve_type (type_l);
                        predicate = value_l->predicate;
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (new llvm::IntToPtrInst (value_l->generated, type_l->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::load:
                    {
                        assert (instruction->predicate_position == 2);
                        auto load_pointer (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (load_pointer);
                        predicate = function_m.process_predicates (load_pointer->predicate, instruction->arguments, 2);
                        auto predicate_branch (llvm::BasicBlock::Create (context));
                        function_m.function_m->getBasicBlockList ().push_back (predicate_branch);
                        auto new_last (llvm::BasicBlock::Create (context));
                        function_m.function_m->getBasicBlockList ().push_back (new_last);
                        function_m.last->getInstList ().push_back (llvm::BranchInst::Create (predicate_branch, new_last, predicate));
                        auto instruction_l (new llvm::LoadInst (load_pointer->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.block_d));
                        predicate_branch->getInstList ().push_back (instruction_l);
                        predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
                        value = function_m.generate_rejoin (function_m.last, predicate_branch, new_last, instruction_l);
                        function_m.last = new_last;
                        break;
                    }
                    case mu::llvmc::instruction_type::lshr:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateLShr (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::mul:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateMul (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::or_i:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateOr (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::ptrtoint:
                    {
                        assert (instruction->predicate_position == 3);
                        auto value_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (value_l);
                        auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
                        function_m.module.retrieve_type (type_l);
                        predicate = value_l->predicate;
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::PtrToIntInst::CreatePointerCast (value_l->generated, type_l->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::sdiv:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateSDiv (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::sext:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
                        function_m.module.retrieve_type (type_l);
                        predicate = function_m.process_predicates (left->predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::SExtInst::CreateSExtOrBitCast (left->generated, type_l->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::shl:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateShl (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::srem:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateSRem (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::store:
                    {
                        assert (false);
                    }
                    case mu::llvmc::instruction_type::sub:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateSub (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.block_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::udiv:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateUDiv (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.block_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::urem:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateURem (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.block_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::xor_i:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
                        function_m.retrieve_value (right);
                        predicate = function_m.and_predicates (left->predicate, right->predicate);
                        predicate = function_m.process_predicates (predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::BinaryOperator::CreateXor (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.block_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    case mu::llvmc::instruction_type::zext:
                    {
                        assert (instruction->predicate_position == 3);
                        auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
                        function_m.retrieve_value (left);
                        auto right (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
                        function_m.module.retrieve_type (right);
                        predicate = function_m.process_predicates (left->predicate, instruction->arguments, 3);
                        auto instruction_l (llvm::SExtInst::CreateZExtOrBitCast (left->generated, right->generated));
                        instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function_m.function_d));
                        function_m.last->getInstList ().push_back (instruction_l);
                        value = instruction_l;
                        break;
                    }
                    default:
                    {
                        assert (false);
                        break;
                    }
                }
                instruction->generated = value;
                instruction->predicate = predicate;
            }
            void icmp (mu::llvmc::skeleton::icmp * icmp) override
            {
                function_m.retrieve_value (icmp->left);
                function_m.retrieve_value (icmp->right);
                auto predicate (function_m.and_predicates (icmp->left->predicate, icmp->right->predicate));
                predicate = function_m.process_predicates (predicate, icmp->predicates, 0);
                llvm::CmpInst::Predicate predicate_t;
                switch (icmp->predicate_m->type)
                {
                    case mu::llvmc::predicates::icmp_eq:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_EQ;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_ne:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_NE;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_ugt:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_UGT;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_uge:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_UGE;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_ult:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_ULT;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_ule:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_ULE;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_sgt:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_SGT;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_sge:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_SGE;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_slt:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_SLT;
                        break;
                    }
                    case mu::llvmc::predicates::icmp_sle:
                    {
                        predicate_t = llvm::CmpInst::Predicate::ICMP_SLE;
                        break;
                    }
                    default:
                        assert (false);
                        break;
                }
                auto instruction_l (new llvm::ICmpInst (predicate_t, icmp->left->generated, icmp->right->generated));
                instruction_l->setDebugLoc (llvm::DebugLoc::get (icmp->region.first.row, icmp->region.first.column, function_m.block_d));
                function_m.last->getInstList ().push_back (instruction_l);
                icmp->generated = instruction_l;
                icmp->predicate = predicate;
            }
            void store (mu::llvmc::skeleton::store * store) override
            {
                function_m.retrieve_value (store->source);
                function_m.retrieve_value (store->destination);
                auto predicate (function_m.and_predicates (store->destination->predicate, store->source->predicate));
                predicate = function_m.process_predicates (predicate, store->predicates, 0);
                auto & context (function_m.module.target.module->getContext ());
                auto predicate_branch (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (predicate_branch);
                auto new_last (llvm::BasicBlock::Create (context));
                function_m.function_m->getBasicBlockList ().push_back (new_last);
                function_m.last->getInstList ().push_back (llvm::BranchInst::Create(predicate_branch, new_last, predicate));
                auto instruction_l (new llvm::StoreInst (store->source->generated, store->destination->generated));
                instruction_l->setDebugLoc (llvm::DebugLoc::get (store->region.first.row, store->region.first.column, function_m.block_d));
                predicate_branch->getInstList ().push_back (instruction_l);
                predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
                store->generated = nullptr;
                store->predicate = predicate;
                function_m.last = new_last;
            }
        };
    }
}

void mu::llvmc::generate_function::retrieve_value (mu::llvmc::skeleton::value * value_a)
{
    assert (value_a != nullptr);
    if (value_a->predicate == nullptr)
    {
        mu::llvmc::generate_value generator (*this);
        value_a->visit (&generator);
    }
    assert (value_a->predicate != nullptr);
}

llvm::Value * mu::llvmc::generate_function::process_predicates (llvm::Value * predicate_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position)
{
    llvm::Value * predicate (predicate_a);
    for (size_t i (predicate_position), j (arguments_a.size ()); i < j; ++i)
    {
        auto & value (arguments_a [i]);
        auto value_l (mu::cast <mu::llvmc::skeleton::value> (value));
        retrieve_value (value_l);
        predicate = and_predicates (predicate, value_l->predicate);
    }
    return predicate;
}

llvm::Value * mu::llvmc::generate_function::generate_rejoin (llvm::BasicBlock * entry, llvm::BasicBlock * predicate, llvm::BasicBlock * successor, llvm::Value * value_a)
{
    auto type (value_a->getType ());
    auto phi (llvm::PHINode::Create (type, 2));
    phi->addIncoming (value_a, predicate);
    phi->addIncoming (llvm::UndefValue::get (type), entry);
    successor->getInstList ().push_back (phi);
    return phi;
}

namespace mu
{
    namespace llvmc
    {
        template <typename T>
        class generate_global : public mu::llvmc::skeleton::visitor
        {
        public:
            generate_global (mu::llvmc::generate_module & module_a, T retrieve_value_a) :
            module (module_a),
            retrieve_value (retrieve_value_a)
            {
            }
            void constant_array (mu::llvmc::skeleton::constant_array * constant_array) override
            {
                std::vector <llvm::Constant *> elements;
                for (auto i: constant_array->initializer)
                {
                    retrieve_value (i);
                    elements.push_back (llvm::cast <llvm::Constant> (i->generated));
                }
                auto type (constant_array->type ());
                module.retrieve_type (type);
                constant_array->generated = llvm::ConstantArray::get (llvm::cast <llvm::ArrayType> (type->generated), llvm::ArrayRef <llvm::Constant *> (elements));
                constant_array->predicate = llvm::ConstantInt::getTrue (module.target.module->getContext ());
            }
            void constant_pointer_null (mu::llvmc::skeleton::constant_pointer_null * value_a) override
            {
                auto type (value_a->type ());
                module.retrieve_type (type);
                value_a->predicate = llvm::ConstantInt::getTrue (module.target.module->getContext ());
                value_a->generated = llvm::ConstantPointerNull::get(llvm::cast <llvm::PointerType> (type->generated));
            }
            void constant_integer (mu::llvmc::skeleton::constant_integer * constant_int) override
            {
                auto type (constant_int->type ());
                module.retrieve_type (type);
                constant_int->predicate = llvm::ConstantInt::getTrue (module.target.module->getContext ());
                constant_int->generated = llvm::ConstantInt::get (type->generated, constant_int->value_m);
            }
            void global_variable (mu::llvmc::skeleton::global_variable * global_variable) override
            {
                retrieve_value (global_variable->initializer);
                auto type (global_variable->initializer->type ());
                module.retrieve_type (type);
                auto global (new llvm::GlobalVariable (type->generated, false, llvm::GlobalValue::LinkageTypes::ExternalLinkage, llvm::cast <llvm::Constant> (global_variable->initializer->generated)));
                global_variable->generated = global;
                global_variable->predicate = global_variable->initializer->predicate;
                module.target.module->getGlobalList ().push_back (global);
            }
            mu::llvmc::generate_module & module;
            T retrieve_value;
        };
    }
}

template <typename T>
void mu::llvmc::generate_module::generate_global (mu::llvmc::skeleton::value * value_a, T retrieve_value_a)
{
    assert (value_a->predicate == nullptr);
    mu::llvmc::generate_global <T> generator (*this, retrieve_value_a);
    value_a->visit (&generator);
    assert (value_a->predicate != nullptr);
}

void mu::llvmc::generate_module::generate_value (mu::llvmc::skeleton::value * value_a)
{
    generate_global (value_a, [=] (mu::llvmc::skeleton::value * value_a) {generate_value (value_a);});
}

llvm::Value * mu::llvmc::generate_function::and_predicates (llvm::Value * left_a, llvm::Value * right_a)
{
    auto and_instruction (llvm::BinaryOperator::CreateAnd (left_a, right_a));
    last->getInstList ().push_back (and_instruction);
    return and_instruction;
}

void mu::llvmc::generate_module::retrieve_type (mu::llvmc::skeleton::type * type_a)
{
    if (type_a->generated == nullptr)
    {
        generate_type (type_a);
    }
    assert (type_a->generated != nullptr);
    assert (type_a->debug.isValid ());
}

namespace mu
{
    namespace llvmc
    {
        class generate_type : public mu::llvmc::skeleton::visitor
        {
        public:
            generate_type (mu::llvmc::generate_module & module_a) :
            module (module_a)
            {
            }
            void node (mu::llvmc::skeleton::node * node_a) override
            {
                // Do nothing
            }
            void integer_type (mu::llvmc::skeleton::integer_type * integer_type) override
            {
                integer_type->generated = llvm::Type::getIntNTy (module.target.module->getContext (), integer_type->bits);
                std::string name ("int");
                char buffer [32];
                sprintf (buffer, "%d", static_cast <int> (integer_type->bits));
                name.append (buffer);
                integer_type->debug = module.builder.createBasicType (name, integer_type->bits, 0, llvm::dwarf::DW_ATE_unsigned);
            }
            void pointer_type (mu::llvmc::skeleton::pointer_type * pointer_type) override
            {
                auto element_type (pointer_type->pointed_type);
                module.retrieve_type (element_type);
                assert (element_type->generated != nullptr);
                assert (element_type->debug != nullptr);
                pointer_type->debug = module.builder.createPointerType (element_type->debug, 8, 0, "ptr");
                pointer_type->generated = llvm::PointerType::get (element_type->generated, 0);
            }
            void unit_type (mu::llvmc::skeleton::unit_type * unit_type) override
            {
                unit_type->generated = llvm::Type::getVoidTy (module.target.module->getContext ());
                unit_type->debug = module.builder.createBasicType ("unit", 0, 0, llvm::dwarf::DW_ATE_unsigned_char);
            }
            void function_type (mu::llvmc::skeleton::function_type * function_type_a) override
            {
                auto & context (module.target.module->getContext ());
                auto function (function_type_a->function);
                std::vector <llvm::Value *> function_type_values;
                function_type_values.push_back (nullptr); // Return type
                std::vector <llvm::Type *> parameters;
                for (auto i (function->parameters.begin ()), j (function->parameters.end ()); i != j; ++i)
                {
                    auto parameter (*i);
                    auto type_s (parameter->type ());
                    module.retrieve_type (type_s);
                    function_type_values.push_back (type_s->debug);
                    parameters.push_back (type_s->generated);
                }
                std::vector <llvm::Value *> results_debug;
                std::vector <llvm::Type *> results;
                uint64_t offset (0);
                function->for_each_results (
                                            [&]
                                            (mu::llvmc::skeleton::result * result_a, size_t)
                                            {
                                                auto type_s (result_a->type);
                                                if (!type_s->is_unit_type())
                                                {
                                                    module.retrieve_type (type_s);
                                                    auto size (type_s->debug.getSizeInBits ());
                                                    auto line (type_s->debug.getLineNumber ());
                                                    auto member (module.builder.createMemberType (module.file, "", module.file, line, size, 0, offset, 0, type_s->debug));
                                                    results_debug.push_back (member);
                                                    results.push_back (type_s->generated);
                                                    offset += size;
                                                }
                                            }
                                            );
                if (function->branch_ends.size () > 1)
                {
                    results.push_back (llvm::Type::getInt8Ty (context));
                    results_debug.push_back (module.builder.createBasicType ("int8", 8, 0, llvm::dwarf::DW_ATE_unsigned_char));
                }
                llvm::Value * result_type_debug;
                llvm::Type * result_type;
                switch (results.size ())
                {
                    case 0:
                        result_type = llvm::Type::getVoidTy (context);
                        result_type_debug = nullptr;
                        break;
                    case 1:
                        result_type = results [0];
                        result_type_debug = llvm::DIDerivedType (llvm::cast <llvm::MDNode> (results_debug [0])).getTypeDerivedFrom ();
                        break;
                    default:
                    {
                        result_type = llvm::StructType::create (context, llvm::ArrayRef <llvm::Type *> (results));
                        auto array (module.builder.getOrCreateArray (llvm::ArrayRef <llvm::Value *> (results_debug)));
                        result_type_debug = module.builder.createStructType (module.file, "", module.file, function->region.first.row, offset, 0, 0, array);
                    }
                }
                function_type_values [0] = result_type_debug;
                auto function_type (llvm::FunctionType::get (result_type, llvm::ArrayRef <llvm::Type *> (parameters), false));
                auto array (module.builder.getOrCreateArray (llvm::ArrayRef <llvm::Value *> (function_type_values)));
                auto function_type_d (module.builder.createSubroutineType (module.file, array));
                function_type_a->generated = function_type;
                function_type_a->debug = function_type_d;
            }
            void array_type (mu::llvmc::skeleton::array_type * array_type) override
            {
                auto & context (module.target.module->getContext ());
                auto type (array_type->element);
                module.retrieve_type (type);
                array_type->generated = llvm::ArrayType::get (type->generated, array_type->size);
                llvm::Value * indicies [2] = {llvm::ConstantInt::get(llvm::Type::getInt64Ty (context), 0), llvm::ConstantInt::get(llvm::Type::getInt64Ty (context), array_type->size)};
                array_type->debug = module.builder.createArrayType (array_type->size, 0, type->debug, module.builder.getOrCreateArray(llvm::ArrayRef <llvm::Value *> (indicies)));
            }
            mu::llvmc::generate_module & module;
        };
    }
}

void mu::llvmc::generate_module::generate_type (mu::llvmc::skeleton::type * type_a)
{
    assert (type_a->generated == nullptr);
    assert (type_a->debug == nullptr);
    mu::llvmc::generate_type generator (*this);
    type_a->visit (&generator);
    assert (type_a->generated != nullptr);
    assert (type_a->debug != nullptr);
}