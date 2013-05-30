#include <mu/llvmc/generator.hpp>

#include <mu/llvmc/ast.hpp>
#include <mu/core/error_string.hpp>
#include <mu/llvmc/skeleton.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>
#include <llvm/InlineAsm.h>
#include <llvm/Support/Dwarf.h>

#include <boost/array.hpp>

#include <gc_cpp.h>

#include <algorithm>

#include <stdlib.h>

mu::llvmc::generator_result mu::llvmc::generator::generate (llvm::LLVMContext & context_a, mu::llvmc::skeleton::module * module_a, mu::string const & name_a, mu::string const & path_a)
{
    mu::llvmc::generator_result result;
    result.module = new llvm::Module ("", context_a);
    mu::llvmc::generate_module generator (module_a, result, name_a, path_a);
    generator.generate ();
    return result;
}

mu::llvmc::generate_module::generate_module (mu::llvmc::skeleton::module * module_a, mu::llvmc::generator_result & target_a, mu::string const & name_a, mu::string const & path_a) :
builder (*target_a.module),
module (module_a),
target (target_a),
file (builder.createFile (std::string (name_a.begin (), name_a.end ()), std::string (path_a.begin (), path_a.end ())))
{
	builder.createCompileUnit (llvm::dwarf::DW_LANG_C, std::string (name_a.begin (), name_a.end ()), std::string (path_a.begin (), path_a.end ()), "MU 0 (Colin LeMahieu)", false, "", 0);
}

void mu::llvmc::generate_module::generate ()
{
    for (auto i (module->functions.begin ()), j (module->functions.end ()); i != j; ++i)
    {
        auto existing (functions.find (i->second));
        if (existing == functions.end ())
        {
            mu::llvmc::generate_function generator_l (*this, i->second);
            generator_l.generate (i->first);
            existing = functions.find (i->second);
            assert (existing != functions.end ());
        }
        assert (target.names.find (i->first) == target.names.end ());
        target.names [i->first] = existing->second;
    }
	builder.finalize ();
}

mu::llvmc::generate_function::generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a) :
module (module_a),
function (function_a),
function_return_type (function_a->get_return_type ())
{
}

void mu::llvmc::generate_function::generate (mu::string const & name_a)
{
    auto & context (module.target.module->getContext ());
	std::vector <llvm::Value *> function_type_values;
	function_type_values.push_back (nullptr); // Return type
    std::vector <llvm::Type *> parameters;
    for (auto i (function->parameters.begin ()), j (function->parameters.end ()); i != j; ++i)
    {
        auto parameter (*i);
		auto type_s (parameter->type ());
        auto type_l (generate_type (type_s));
		auto existing (type_information.find (type_s));
		assert (existing != type_information.end ());
		function_type_values.push_back (existing->second);
        parameters.push_back (type_l);
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
               auto type_l (generate_type (type_s));
			   auto existing (type_information.find (type_s));
			   assert (existing != type_information.end ());
			   auto size (existing->second.getSizeInBits ());
			   auto member (module.builder.createMemberType (module.file, "", module.file, 0, size, 0, offset, 0, existing->second));
			   results_debug.push_back (member);
               results.push_back (type_l);
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
			result_type_debug = results_debug [0];
            break;
        default:
        {
            result_type = llvm::StructType::create (context, llvm::ArrayRef <llvm::Type *> (results));
			auto array (module.builder.getOrCreateArray (llvm::ArrayRef <llvm::Value *> (results_debug)));
			result_type_debug = module.builder.createStructType (module.file, "", module.file, 0, offset, 0, 0, array);
        }
    }
	function_type_values [0] = result_type_debug;
    auto function_type (llvm::FunctionType::get (result_type, llvm::ArrayRef <llvm::Type *> (parameters), false));
    auto function_l (llvm::Function::Create (function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage));	
	auto array (module.builder.getOrCreateArray (llvm::ArrayRef <llvm::Value *> (function_type_values)));
	auto function_type_d (module.builder.createSubroutineType (module.file, array));
	auto function_d (module.builder.createFunction (module.file, std::string (name_a.begin (), name_a.end ()), std::string (name_a.begin (), name_a.end ()), module.file, 0, function_type_d, false, true, 0));
    {
        auto i (function_l->arg_begin());
        auto j (function_l->arg_end());
        auto k (function->parameters.begin ());
        auto l (function->parameters.end ());
        for (; i != j; ++i, ++k)
        {
            assert (k != l);
            llvm::Value * parameter (i);
            already_generated [*k] = mu::llvmc::value_data ({llvm::ConstantInt::getTrue (context), parameter});
        }
        assert ((i != j) == (k != l));
    }
    function_m = function_l;
    module.target.module->getFunctionList ().push_back (function_l);
    assert (module.functions.find (function) == module.functions.end ());
    module.functions [function] = function_l;
    auto entry (llvm::BasicBlock::Create (context));
    last = entry;
    function_l->getBasicBlockList ().push_back (entry);
    switch (function_return_type)
    {
        case mu::llvmc::skeleton::function_return_type::b0:
        {
            last->getInstList ().push_back (new llvm::UnreachableInst (function_l->getContext ()));
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1v0:
        {
            function->for_each_results (
                [&]
                (mu::llvmc::skeleton::result * result_a, size_t)
                {
                    auto result (retrieve_value (result_a->value));
                    assert (result_a->type->is_unit_type ());
                },
                [&]
                (mu::llvmc::skeleton::value * value_a, size_t)
                {
                    auto result (retrieve_value (value_a));
                }
            );
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext ()));
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1v1:
        {
            llvm::Value * the_value (nullptr);
            function->for_each_results (
                [&]
                (mu::llvmc::skeleton::result * result_a, size_t)
                {
                    auto result (retrieve_value (result_a->value));
                    assert (the_value == nullptr || result_a->type->is_unit_type ());
                    the_value = result_a->type->is_unit_type () ? the_value : result.value;
                },
                [&]
                (mu::llvmc::skeleton::value * value_a, size_t)
                {
                    auto result (retrieve_value (value_a));
                }
            );
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext (), the_value));
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
                    auto result_value (retrieve_value (result_a->value));
                    if (!result_a->type->is_unit_type ())
                    {
                        auto insert = llvm::InsertValueInst::Create (result, result_value.value, llvm::ArrayRef <unsigned> (index));
                        last->getInstList ().push_back (insert);
                        result = insert;
                        ++index;
                    }
                },
                [&]
                (mu::llvmc::skeleton::value * value_a, size_t)
                {
                    auto result (retrieve_value (value_a));
                }
            );
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext (), result));
            break;
        }
        case mu::llvmc::skeleton::function_return_type::bmv0:
        {
            auto results (generate_result_set ());
            assert (results.size () == 1);
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext (), results [0]));
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
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext (), result));
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
            auto result_l (retrieve_value (result_a->value));
            if (!result_a->type->is_unit_type())
            {
                result.push_back (result_l.value);
            }
            auto instruction (llvm::BinaryOperator::CreateAnd (predicate, result_l.predicate));
            last->getInstList ().push_back (instruction);
            predicate = instruction;
        },
        [&]
        (mu::llvmc::skeleton::value * value_a, size_t)
        {
            auto result (retrieve_value (value_a));
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

mu::llvmc::value_data mu::llvmc::generate_function::retrieve_value (mu::llvmc::skeleton::value * value_a)
{
    assert (value_a != nullptr);
    mu::llvmc::value_data result;
    auto existing (already_generated.find (value_a));
    if (existing == already_generated.end ())
    {
        result = generate_value (value_a);
    }
    else
    {
        result = existing->second;
    }
    return result;
}

mu::llvmc::value_data mu::llvmc::generate_function::generate_value (mu::llvmc::skeleton::value * value_a)
{
    assert (value_a != nullptr);
	assert (dynamic_cast <mu::llvmc::skeleton::parameter *> (value_a) == nullptr);
	assert (dynamic_cast <mu::llvmc::skeleton::loop_parameter *> (value_a) == nullptr);
    assert (already_generated.find (value_a) == already_generated.end ());
    mu::llvmc::value_data result;
    auto call (dynamic_cast <mu::llvmc::skeleton::call_element_value *> (value_a));
    if (call != nullptr)
    {
        auto & context (module.target.module->getContext ());
        llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
        assert (call->source->arguments.size () > 0);
        assert (dynamic_cast <mu::llvmc::skeleton::value *> (call->source->arguments [0]) != nullptr);
        auto existing (module.functions.find (call->source->target));
        if (existing == module.functions.end ())
        {
            mu::llvmc::generate_function generator (module, call->source->target);
            generator.generate (U"");
        }
        assert (module.functions.find (call->source->target) != module.functions.end ());
        auto function (module.functions [call->source->target]);
        std::vector <llvm::Value *> arguments;
        size_t position (1);
        auto end (call->source->predicate_offset);
        for (auto i (call->source->arguments.begin () + 1); position < end; ++i, ++position)
        {
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (*i) != nullptr);
            auto argument (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (*i)));
            auto instruction (llvm::BinaryOperator::CreateAnd (predicate, argument.predicate));
            last->getInstList ().push_back (instruction);
            predicate = instruction;
            assert (argument.value != nullptr);
            arguments.push_back (argument.value);
        }
        predicate = process_predicates (predicate, call->source->arguments, position + 1);
        auto call_block (llvm::BasicBlock::Create (context));
        function_m->getBasicBlockList ().push_back (call_block);
        auto new_last (llvm::BasicBlock::Create (context));
        function_m->getBasicBlockList ().push_back (new_last);
        auto return_type (call->source->target->get_return_type ());
        switch (return_type)
        {
            case mu::llvmc::skeleton::function_return_type::b0:
            {
                auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                call_block->getInstList ().push_back (call_l);
                already_generated [value_a] = mu::llvmc::value_data ({predicate, nullptr});
                break;
            }
            case mu::llvmc::skeleton::function_return_type::b1v0:
            {
                auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                call_block->getInstList ().push_back (call_l);
                already_generated [value_a] = mu::llvmc::value_data ({predicate, nullptr});
                break;
            }
            case mu::llvmc::skeleton::function_return_type::b1v1:
            {
                auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                call_block->getInstList ().push_back (call_l);
                auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
                new_last->getInstList ().push_back (real_call);
                real_call->addIncoming (call_l, call_block);
                real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), last);
                already_generated [value_a] = mu::llvmc::value_data ({predicate, real_call});
                break;
            }
            case mu::llvmc::skeleton::function_return_type::b1vm:
            {
                auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                call_block->getInstList ().push_back (call_l);
                unsigned position (0);
                auto k (call->source->elements.begin ());
                auto l (call->source->elements.end ());
                call->source->target->for_each_results (
                    [&]
                    (mu::llvmc::skeleton::result * result_a, size_t)
                    {
                        auto element (llvm::ExtractValueInst::Create (call_l, position));
                        call_block->getInstList ().push_back (element);
                        auto real_element (llvm::PHINode::Create (element->getType (), 2));
                        new_last->getInstList ().push_back (real_element);
                        real_element->addIncoming (element, call_block);
                        real_element->addIncoming (llvm::UndefValue::get (element->getType ()), last);
                        already_generated [*k] = mu::llvmc::value_data ({predicate, real_element});
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
                call_block->getInstList ().push_back (call_l);
                auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
                new_last->getInstList ().push_back (real_call);
                real_call->addIncoming (call_l, call_block);
                real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), last);
                unsigned position (0);
                auto selector_type (llvm::Type::getInt8Ty (context));
                auto k (call->source->elements.begin ());
                auto l (call->source->elements.end ());
                call->source->target->for_each_results (
                    [&]
                    (mu::llvmc::skeleton::result *, size_t)
                    {
                        auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, real_call, llvm::ConstantInt::get (selector_type, position)));
                        new_last->getInstList ().push_back (compare);
                        auto instruction (llvm::BinaryOperator::CreateAnd (predicate, compare));
                        new_last->getInstList ().push_back (instruction);
                        already_generated [*k] = mu::llvmc::value_data ({instruction, nullptr});
                        ++k;
                        ++position;
                    });
                assert (k == l);
                break;
            }
            case mu::llvmc::skeleton::function_return_type::bmvm:
            {
                auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
                call_block->getInstList ().push_back (call_l);
                auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
                new_last->getInstList ().push_back (real_call);
                real_call->addIncoming (call_l, call_block);
                real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), last);
                auto function_result (llvm::cast <llvm::StructType> (call_l->getType ()));
                assert (function_result->getNumElements () > 1);
                auto selector (llvm::ExtractValueInst::Create (real_call, llvm::ArrayRef <unsigned> (function_result->getNumElements () - 1)));
                new_last->getInstList ().push_back (selector);
                auto selector_type (llvm::Type::getInt8Ty (context));
                auto current_element (call->source->elements.begin ());
                auto end_element (call->source->elements.end ());
                size_t current_selector (0);
                unsigned result_index (0);
                auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, selector, llvm::ConstantInt::get (selector_type, current_selector)));
                new_last->getInstList ().push_back (compare);
                auto instruction (llvm::BinaryOperator::CreateAnd (predicate, compare));
                new_last->getInstList ().push_back (instruction);
                call->source->target->for_each_results (
                    [&]
                    (mu::llvmc::skeleton::result * result_a, size_t)
                    {
                        assert (current_element != end_element);
                        if (!result_a->type->is_unit_type ())
                        {
                            auto extraction (llvm::ExtractValueInst::Create (real_call, llvm::ArrayRef <unsigned> (result_index)));
                            new_last->getInstList().push_back (extraction);
                            already_generated [*current_element] = mu::llvmc::value_data ({instruction, extraction});
                            ++result_index;
                            ++current_element;
                        }
                        else
                        {
                            already_generated [*current_element] = mu::llvmc::value_data ({instruction, nullptr});
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
                    });
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
        last->getInstList ().push_back (call_branch);
        last = new_last;
        assert (already_generated.find (value_a) != already_generated.end ());
        result = already_generated [value_a];
    }
    else
    {
        auto element (dynamic_cast <mu::llvmc::skeleton::switch_element *> (value_a));
        if (element != nullptr)
        {
            assert (element->source->arguments.size () > 1);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (element->source->arguments [1]) != nullptr);
            llvm::Value * predicate (llvm::ConstantInt::getTrue (last->getContext ()));
            auto predicate_l (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (element->source->arguments [1])));
            auto instruction (llvm::BinaryOperator::CreateAnd (predicate, predicate_l.predicate));
            last->getInstList ().push_back (instruction);
            predicate = instruction;
            auto & elements (element->source->elements);
            size_t position (0);
            for (auto i (elements.begin ()); *i != nullptr; ++i, ++position)
            {
                auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, predicate_l.value, llvm::ConstantInt::get (predicate_l.value->getType (), (*i)->value_m->value_m)));
                last->getInstList().push_back (compare);
                auto switch_predicate (llvm::BinaryOperator::CreateAnd (predicate, compare));
                last->getInstList().push_back (switch_predicate);
                already_generated [*i] = mu::llvmc::value_data ({switch_predicate, nullptr});
            }
            predicate = process_predicates (predicate, element->source->arguments, position);
            result = already_generated [value_a];
        }
        else
        {
			auto loop_element (dynamic_cast <mu::llvmc::skeleton::loop_element *> (value_a));
			if (loop_element != nullptr)
			{
				auto & context (module.target.module->getContext ());
				llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
				std::vector <llvm::PHINode *> parameters;
				auto loop_entry (llvm::BasicBlock::Create (context));
				function_m->getBasicBlockList ().push_back (loop_entry);
				{
					size_t position (0);
					auto end (loop_element->source->argument_predicate_offset);
                    assert (loop_element->source->arguments.size () >= loop_element->source->argument_predicate_offset);
					for (auto i (loop_element->source->arguments.begin ()); position < end; ++i, ++position)
					{
                        assert (i != loop_element->source->arguments.end ());
						assert (dynamic_cast <mu::llvmc::skeleton::value *> (*i) != nullptr);
						auto value (static_cast <mu::llvmc::skeleton::value *> (*i));
						auto argument_l (retrieve_value (value));
						predicate = and_predicates (predicate, argument_l.predicate);
						auto loop_parameter (llvm::PHINode::Create (argument_l.value->getType (), 2));
						loop_parameter->addIncoming (argument_l.value, last);
						loop_entry->getInstList ().push_back (loop_parameter);
						assert (position < loop_element->source->parameters.size ());
						already_generated [loop_element->source->parameters [position]] = mu::llvmc::value_data ({predicate, loop_parameter});
						parameters.push_back (loop_parameter);
					}
					assert (position == loop_element->source->parameters.size ());
				}
				auto entry (last);
				auto successor (llvm::BasicBlock::Create (context));
				function_m->getBasicBlockList ().push_back (successor);
				entry->getInstList ().push_back (llvm::BranchInst::Create (loop_entry, successor, predicate));
				last = loop_entry;
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
						assert (dynamic_cast <mu::llvmc::skeleton::value *> (node_a));
						empty = false;
						auto value (static_cast <mu::llvmc::skeleton::value *> (node_a));
						auto result_l (retrieve_value (value));
						branch_predicate = and_predicates (branch_predicate, result_l.predicate);
						if (feedback_branch)
						{
							assert (parameter_position < parameters.size ());
							parameters [parameter_position]->addIncoming (result_l.value, last);
							++parameter_position;
						}
						else
						{
							auto real_value (llvm::PHINode::Create (result_l.value->getType (), 2));
							real_value->addIncoming (llvm::UndefValue::get (result_l.value->getType ()), last);
							real_value->addIncoming (result_l.value, last);
							successor->getInstList ().push_back (real_value);
							parameters.push_back (real_value);
							auto real_predicate (llvm::PHINode::Create (result_l.predicate->getType (), 2));
							real_predicate->addIncoming (llvm::UndefValue::get (result_l.predicate->getType ()), last);
							real_predicate->addIncoming (result_l.predicate, last);
							successor->getInstList ().push_back (real_predicate);
							parameters.push_back (real_predicate);
							assert (element_position < loop_element->source->elements.size ());
							already_generated [loop_element->source->elements [element_position]] = mu::llvmc::value_data ({real_predicate, real_value});
							++element_position;
						}
					},
					[&]
					(mu::llvmc::skeleton::node * node_a, size_t)
					{
						assert (dynamic_cast <mu::llvmc::skeleton::value *> (node_a));
						auto value (static_cast <mu::llvmc::skeleton::value *> (node_a));
						auto result_l (retrieve_value (value));
						branch_predicate = and_predicates (branch_predicate, result_l.predicate);
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
							real_predicate->addIncoming (llvm::UndefValue::get (branch_predicate->getType ()), last);
							real_predicate->addIncoming (branch_predicate, last);
							successor->getInstList ().push_back (real_predicate);
							parameters.push_back (real_predicate);
							assert (element_position < loop_element->source->elements.size ());
							already_generated [loop_element->source->elements [element_position]] = mu::llvmc::value_data ({real_predicate, nullptr});
							++element_position;
						}
						empty = true;
						branch_predicate = predicate;
					}
				);
				for (auto i: parameters)
				{
					i->setIncomingBlock (0, entry);
					i->setIncomingBlock (1, last);
				}
				auto feedback (llvm::BranchInst::Create (loop_entry, successor, feedback_predicate));
				last->getInstList ().push_back (feedback);
				last = successor;
				assert (already_generated.find (value_a) != already_generated.end ());
				result = already_generated [value_a];
			}
			else
			{
				result = generate_single (value_a);
			}
        }
    }
    return result;
}

llvm::Value * mu::llvmc::generate_function::process_predicates (llvm::Value * predicate_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position)
{
    auto last_l (last);
    llvm::Value * predicate (predicate_a);
    for (size_t i (predicate_position), j (arguments_a.size ()); i < j; ++i)
    {
        auto & value (arguments_a [i]);
        assert (dynamic_cast <mu::llvmc::skeleton::value *> (value) != nullptr);
        auto value_l (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (value)));
        predicate = and_predicates (predicate, value_l.predicate);
    }
    return predicate;
}

mu::llvmc::value_data mu::llvmc::generate_function::generate_single (mu::llvmc::skeleton::value * value_a)
{
    assert (value_a != nullptr);
    assert (already_generated.find (value_a) == already_generated.end ());
    auto & context (module.target.module->getContext ());
    llvm::Value * predicate;
    llvm::Value * value;
    auto constant_aggregate_zero (dynamic_cast <mu::llvmc::skeleton::constant_aggregate_zero *> (value_a));
    if (constant_aggregate_zero != nullptr)
    {
        auto type (generate_type (value_a->type ()));;
        predicate = llvm::ConstantInt::getTrue (module.target.module->getContext ());
        value = llvm::ConstantAggregateZero::get (type);
    }
    else
    {
        auto constant_pointer_null (dynamic_cast <mu::llvmc::skeleton::constant_pointer_null *> (value_a));
        if (constant_pointer_null != nullptr)
        {
            auto type (generate_type (value_a->type ()));
            predicate = llvm::ConstantInt::getTrue (module.target.module->getContext ());
            value = llvm::ConstantPointerNull::get(llvm::cast <llvm::PointerType> (type));
        }
        else
        {
            auto constant_int (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (value_a));
            if (constant_int != nullptr)
            {
                auto type (generate_type (value_a->type ()));
                predicate = llvm::ConstantInt::getTrue (module.target.module->getContext ());
                value = llvm::ConstantInt::get (type, constant_int->value_m);
            }
            else
            {
                auto instruction (dynamic_cast <mu::llvmc::skeleton::instruction *> (value_a));
                if (instruction != nullptr)
                {
                    switch (instruction->marker ())
                    {
                        case mu::llvmc::instruction_type::add:
                        {
                            assert (instruction->predicate_position == 3);
                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                            auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2]) != nullptr);
                            auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2])));
                            predicate = and_predicates (left.predicate, right.predicate);
                            predicate = process_predicates (predicate, instruction->arguments, 3);
                            auto instruction (llvm::BinaryOperator::CreateAdd (left.value, right.value));
                            last->getInstList ().push_back (instruction);
                            value = instruction;
                            break;
                        }
						case mu::llvmc::instruction_type::icmp:
						{
							assert (instruction->predicate_position == 4);
							assert (dynamic_cast <mu::llvmc::skeleton::predicate *> (instruction->arguments [1]) != nullptr);
							auto predicate_l (static_cast <mu::llvmc::skeleton::predicate *> (instruction->arguments [1]));
							assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2]) != nullptr);
                            auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2])));
							assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [3]) != nullptr);
                            auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [3])));
							predicate = and_predicates (left.predicate, right.predicate);
							predicate = process_predicates (predicate, instruction->arguments, 4);
							llvm::CmpInst::Predicate predicate_t;
							switch (predicate_l->type)
							{
								case mu::llvmc::predicates::icmp_eq:
								{
									predicate_t = llvm::CmpInst::Predicate::ICMP_EQ;
									break;
								}
								default:
									assert (false);
									break;
							}
							auto instruction (new llvm::ICmpInst (predicate_t, left.value, right.value));
                            last->getInstList ().push_back (instruction);
                            value = instruction;
							break;
						}
                        case mu::llvmc::instruction_type::load:
                        {
                            assert (instruction->predicate_position == 2);
                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                            auto load_pointer (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                            predicate = process_predicates (load_pointer.predicate, instruction->arguments, 2);
                            auto predicate_branch (llvm::BasicBlock::Create (context));
                            function_m->getBasicBlockList ().push_back (predicate_branch);
                            auto new_last (llvm::BasicBlock::Create (context));
                            function_m->getBasicBlockList ().push_back (new_last);
                            last->getInstList ().push_back (llvm::BranchInst::Create (predicate_branch, new_last, predicate));
                            auto instruction_l (new llvm::LoadInst (load_pointer.value));
                            predicate_branch->getInstList ().push_back (instruction_l);
                            predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
                            auto phi (llvm::PHINode::Create (instruction_l->getType (), 2));
                            new_last->getInstList ().push_back (phi);
                            phi->addIncoming (instruction_l, predicate_branch);
                            phi->addIncoming (llvm::UndefValue::get (instruction_l->getType ()), last);
                            value = phi;
                            last = new_last;
                            break;
                        }
                        case mu::llvmc::instruction_type::store:
                        {
                            assert (instruction->predicate_position == 3);
                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2]) != nullptr);
                            auto store_value (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                            auto store_pointer (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2])));
                            predicate = and_predicates (store_pointer.predicate, store_value.predicate);
                            predicate = process_predicates (predicate, instruction->arguments, 3);
                            auto predicate_branch (llvm::BasicBlock::Create (context));
                            function_m->getBasicBlockList ().push_back (predicate_branch);
                            auto new_last (llvm::BasicBlock::Create (context));
                            function_m->getBasicBlockList ().push_back (new_last);
                            last->getInstList ().push_back (llvm::BranchInst::Create(predicate_branch, new_last, predicate));
                            auto instruction_l (new llvm::StoreInst (store_value.value, store_pointer.value));
                            predicate_branch->getInstList ().push_back (instruction_l);
                            predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
                            value = nullptr;
                            last = new_last;
                            break;
                        }
                        case mu::llvmc::instruction_type::sub:
                        {
                            assert (instruction->predicate_position == 3);
                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                            auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                            assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2]) != nullptr);
                            auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2])));
                            predicate = and_predicates (left.predicate, right.predicate);
                            predicate = process_predicates (predicate, instruction->arguments, 3);
                            auto instruction (llvm::BinaryOperator::CreateSub (left.value, right.value));
                            last->getInstList ().push_back (instruction);
                            value = instruction;
                            break;
                        }
                        default:
                        {
                            assert (false);
                            break;
                        }
                    }
                }
                else
                {
                    auto join (dynamic_cast <mu::llvmc::skeleton::join_value *> (value_a));
                    if (join != nullptr)
                    {
                        assert (join->arguments.size () > 1);
                        auto unit (join->arguments [0]->type ()->is_unit_type ());
                        predicate = llvm::ConstantInt::getFalse (function_m->getContext ());
                        auto first (retrieve_value (join->arguments [0]));
                        assert (unit == (first.value == nullptr));
                        if (!unit)
                        {
                            value = llvm::UndefValue::get (first.value->getType ());
                        }
                        else
                        {
                            value = nullptr;
                        }
                        for (auto i: join->arguments)
                        {
                            auto value_l (retrieve_value (i));
                            auto predicate_instruction (llvm::BinaryOperator::CreateOr (predicate, value_l.predicate));
                            last->getInstList ().push_back (predicate_instruction);
                            if (!unit)
                            {
                                auto select_instruction (llvm::SelectInst::Create (value_l.predicate, value_l.value, value));
                                last->getInstList ().push_back (select_instruction);
                                value = select_instruction;
                            }
                            predicate = predicate_instruction;
                        }
                        
                    }
                    else
                    {
                        auto unit (dynamic_cast <mu::llvmc::skeleton::unit_value *> (value_a));
                        if (unit != nullptr)
                        {
                            value = nullptr;
                            predicate = llvm::ConstantInt::getTrue (context);
                        }
                        else
                        {
							auto asm_l (dynamic_cast <mu::llvmc::skeleton::inline_asm *> (value_a));
							if (asm_l != nullptr)
							{
								assert (asm_l->arguments.size () > 0);
								assert (dynamic_cast <mu::llvmc::skeleton::asm_c *> (asm_l->arguments [0]) != nullptr);
								auto info (static_cast <mu::llvmc::skeleton::asm_c *> (asm_l->arguments [0]));
								auto end (asm_l->predicate_position);
								predicate = llvm::ConstantInt::getTrue (context);
								std::vector <llvm::Type *> types;
								std::vector <llvm::Value *> arguments;
								size_t i (1);
								for (; i < end; ++i)
								{
									assert (dynamic_cast <mu::llvmc::skeleton::value *> (asm_l->arguments [i]) != nullptr);
									auto value (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (asm_l->arguments [i])));
									predicate = and_predicates (predicate, value.predicate);
									if (value.value != nullptr)
									{
										arguments.push_back (value.value);
										types.push_back (value.value->getType ());
									}
								}
								for (size_t j (asm_l->arguments.size ()); i < j; ++i)
								{
									assert (dynamic_cast <mu::llvmc::skeleton::value *> (asm_l->arguments [i]) != nullptr);
									auto value (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (asm_l->arguments [i])));
									predicate = and_predicates (predicate, value.predicate);
								}
								llvm::Type * type;
								if (!info->type_m->is_unit_type ())
								{
									type = generate_type (info->type_m);
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
								function_m->getBasicBlockList ().push_back (call_block);
								auto successor (llvm::BasicBlock::Create (context));
								function_m->getBasicBlockList ().push_back (successor);
								auto predicate_branch (llvm::BranchInst::Create (call_block, successor, predicate));
								last->getInstList ().push_back (predicate_branch);
								call_block->getInstList ().push_back (call);
								auto rejoin (llvm::BranchInst::Create (successor));
								call_block->getInstList ().push_back (rejoin);
								last = successor;
							}
							else
							{
								assert (false);
							}
                        }
                    }
                }
            }
        }
    }
    assert (predicate != nullptr);
    auto result (mu::llvmc::value_data ({predicate, value}));
    already_generated [value_a] = result;
    return result;
}

llvm::Value * mu::llvmc::generate_function::and_predicates (llvm::Value * left_a, llvm::Value * right_a)
{
    auto and_instruction (llvm::BinaryOperator::CreateAnd (left_a, right_a));
    last->getInstList ().push_back (and_instruction);
    return and_instruction;
}

llvm::Type * mu::llvmc::generate_function::generate_type (mu::llvmc::skeleton::type * type_a)
{
    assert (!type_a->is_unit_type ());
    llvm::Type * result;
    auto integer_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type_a));
    if (integer_type != nullptr)
    {
        result = llvm::Type::getIntNTy (module.target.module->getContext (), integer_type->bits);
		std::string name ("int");
		char buffer [32];
		sprintf (buffer, "%d", static_cast <int> (integer_type->bits));
		name.append (buffer);
		type_information [type_a] = module.builder.createBasicType (name, integer_type->bits, 0, llvm::dwarf::DW_ATE_unsigned);
    }
    else
    {
        auto pointer_type (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (type_a));
        if (pointer_type != nullptr)
        {
            auto element_type (generate_type (pointer_type->pointed_type));
            assert (element_type != nullptr);
			auto existing (type_information.find (pointer_type->pointed_type));
			assert (existing != type_information.end ());
			type_information [type_a] = module.builder.createPointerType (existing->second, 8);
            result = llvm::PointerType::get (element_type, 0);
        }
        else
        {
            assert (false && "Unknown type");
        }
    }
	assert (type_information.find (type_a) != type_information.end ());
    return result;
}