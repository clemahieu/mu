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
	mu::llvmc::generate_system generator (context_a, name_a, path_a, module_id_a);
	module_a->visit (&generator);
    return generator.result;
}

void mu::llvmc::generate_system::module (mu::llvmc::skeleton::module * node_a)
{
    mu::llvmc::generate_module generator (*this, node_a);
	generator.generate ();
	if (node_a->entry != nullptr)
	{
		assert (node_a->entry->generated != nullptr);
		result.entry = llvm::cast <llvm::Function> (node_a->entry->generated);
	}
}

mu::llvmc::generate_module::generate_module (mu::llvmc::generate_system & system_a, mu::llvmc::skeleton::module * module_a) :
builder (*system_a.result.module),
module (module_a),
global_id (0),
previous (system_a.current_generator),
system (system_a)
{
	system_a.current_generator = this;
	builder.createCompileUnit (llvm::dwarf::DW_LANG_C, std::string (system.name.begin (), system.name.end ()), std::string (system.path.begin (), system.path.end ()), "MU 0 (Colin LeMahieu)", false, "", 0);
    file = builder.createFile (std::string (system.name.begin (), system.name.end ()), std::string (system.path.begin (), system.path.end ()));
}

mu::llvmc::generate_module::~generate_module ()
{
	assert (system.current_generator == this);
	system.current_generator = previous;
}

void mu::llvmc::generate_module::generate ()
{
    for (auto i (module->globals.begin ()), j (module->globals.end ()); i != j; ++i)
    {
        system.generate_value (*i);
	}
	builder.finalize ();
}

mu::llvmc::generate_function::generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a) :
module (module_a),
function (function_a),
function_return_type (function_a->get_return_type ()),
previous (module_a.system.current_generator)
{
	module_a.system.current_generator = this;
}

mu::llvmc::generate_function::~generate_function ()
{
	assert (module.system.current_generator == this);
	module.system.current_generator = previous;
}

void mu::llvmc::generate_function::generate ()
{
    auto & context (module.system.result.module->getContext ());
    assert (function->predicate != nullptr);
    auto function_l (llvm::cast <llvm::Function> (function->generated));
    auto type (&function->type_m);
    module.system.generate_type (type);
    auto function_type (llvm::cast <llvm::FunctionType> (type->generated));
    block_d = module.builder.createLexicalBlock (function->debug, module.file, function->region.first.row, function->region.first.column);
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
			auto alloc (new llvm::AllocaInst (parameter->getType ()));
			entry->getInstList ().push_back (alloc);
			auto variable_info (module.builder.createLocalVariable (llvm::dwarf::DW_TAG_auto_variable, function->debug, std::string (name.begin (), name.end ()), module.file, 0, existing->debug));
			auto store (new llvm::StoreInst (parameter, alloc));
			entry->getInstList ().push_back (store);
            auto declaration (module.builder.insertDeclare (alloc, variable_info, entry));
			declaration->setDebugLoc (llvm::DebugLoc::get (value->region.last.row, value->region.last.column, function->debug));
        }
        assert ((i != j) == (k != l));
    }
    switch (function_return_type)
    {
        case mu::llvmc::skeleton::function_return_type::b0:
        {
            auto ret (new llvm::UnreachableInst (function_l->getContext ()));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function->debug));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1v0:
        {
            assert (function->results.size () == 1);
            auto & result_l (function->results [0]);
            for (auto i: result_l.results)
            {
                auto result (mu::cast <mu::llvmc::skeleton::result> (i));
                module.system.generate_value (result->value);
                assert (result->type->is_unit_type ());
            }
            for (auto i: result_l.sequenced)
            {
                module.system.generate_value (i);
            }
            auto ret (llvm::ReturnInst::Create (function_l->getContext ()));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function->debug));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1v1:
        {
            llvm::Value * the_value (nullptr);
            assert (function->results.size () == 1);
            auto & result_l (function->results [0]);
            for (auto i: result_l.results)
            {
                auto result (mu::cast <mu::llvmc::skeleton::result> (i));
                module.system.generate_value (result->value);
                assert (the_value == nullptr || result->type->is_unit_type ());
                the_value = result->type->is_unit_type () ? the_value : result->value->generated;
            }
            for (auto i: result_l.sequenced)
            {
                module.system.generate_value (i);
            }
            auto ret (llvm::ReturnInst::Create (function_l->getContext (), the_value));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function->debug));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::b1vm:
        {
            llvm::Value * result (llvm::UndefValue::get (function_type->getReturnType ()));
            unsigned index (0);
            assert (function->results.size () == 1);
            auto & result_l (function->results [0]);
            for (auto i: result_l.results)
            {
                auto result_l (mu::cast <mu::llvmc::skeleton::result> (i));
                module.system.generate_value (result_l->value);
                if (!result_l->type->is_unit_type ())
                {
                    auto insert = llvm::InsertValueInst::Create (result, result_l->value->generated, llvm::ArrayRef <unsigned> (index));
                    last->getInstList ().push_back (insert);
                    result = insert;
                    ++index;
                }
            }
            for (auto i: result_l.sequenced)
            {
                module.system.generate_value (i);
            }
            assert (index > 1);
            auto ret (llvm::ReturnInst::Create (function_l->getContext (), result));            
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function->debug));
            last->getInstList ().push_back (ret);
            break;
        }
        case mu::llvmc::skeleton::function_return_type::bmv0:
        {
            auto results (generate_result_set ());
            assert (results.size () == 1);
            auto ret (llvm::ReturnInst::Create (function_l->getContext (), results [0]));
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function->debug));
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
            ret->setDebugLoc (llvm::DebugLoc::get (function->region.last.row, function->region.last.column, function->debug));
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
    for (auto & i: function->results.branches)
    {
        for (auto j: i.results)
        {
            auto result_l (mu::cast <mu::llvmc::skeleton::result> (j));
            module.system.generate_value (result_l->value);
            if (!result_l->type->is_unit_type())
            {
                result.push_back (result_l->value->generated);
            }
            auto instruction (llvm::BinaryOperator::CreateAnd (predicate, result_l->value->predicate));
            last->getInstList ().push_back (instruction);
            predicate = instruction;
        }
        for (auto j: i.sequenced)
        {
            module.system.generate_value (j);
        }
        auto selector_new (llvm::SelectInst::Create (predicate, llvm::ConstantInt::get (type, selector_number), selector));
        last->getInstList().push_back (selector_new);
        selector = selector_new;
        predicate = llvm::ConstantInt::getTrue (context);
        ++selector_number;
    }
    result.push_back (selector);
    return result;
}

void mu::llvmc::generate_function::call_element (mu::llvmc::skeleton::call_element * node_a)
{
	auto call_a (node_a->source);
	auto & context (module.system.result.module->getContext ());
	llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
	assert (call_a->arguments.size () > 0);
	module.system.generate_value (mu::cast <mu::llvmc::skeleton::value> (call_a->target));
	auto function (call_a->target->generated);
	assert (function != nullptr);
	std::vector <llvm::Value *> arguments;
	size_t position (1);
	for (auto i (call_a->arguments.begin () + 1), j (call_a->arguments.end ()); i < j; ++i, ++position)
	{
		auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
		module.system.generate_value (value);
		auto instruction (llvm::BinaryOperator::CreateAnd (predicate, value->predicate));
		last->getInstList ().push_back (instruction);
		predicate = instruction;
		assert (value->predicate != nullptr);
		arguments.push_back (value->generated);
	}
	predicate = process_predicates (predicate, call_a->sequenced);
	auto call_block (llvm::BasicBlock::Create (context));
	function_m->getBasicBlockList ().push_back (call_block);
	auto new_last (llvm::BasicBlock::Create (context));
	function_m->getBasicBlockList ().push_back (new_last);
	auto return_type (call_a->target->get_return_type ());
	switch (return_type)
	{
		case mu::llvmc::skeleton::function_return_type::b0:
		{
			auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
			assert (call_a->elements.size () == 1);
			call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, block_d));
			call_block->getInstList ().push_back (call_l);
			call_a->elements [0]->generated = nullptr;
			call_a->elements [0]->predicate = predicate;
			break;
		}
		case mu::llvmc::skeleton::function_return_type::b1v0:
		{
			auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
			assert (call_a->elements.size () == 1);
			call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, block_d));
			call_block->getInstList ().push_back (call_l);
			call_a->elements [0]->generated = nullptr;
			call_a->elements [0]->predicate = predicate;
			break;
		}
		case mu::llvmc::skeleton::function_return_type::b1v1:
		{
			auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
			assert (call_a->elements.size () == 1);
			call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, block_d));
			call_block->getInstList ().push_back (call_l);
			auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
			new_last->getInstList ().push_back (real_call);
			real_call->addIncoming (call_l, call_block);
			real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), last);
			call_a->elements [0]->generated = real_call;
			call_a->elements [0]->predicate = predicate;
			break;
		}
		case mu::llvmc::skeleton::function_return_type::b1vm:
		{
			auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
			assert (call_a->elements.size () > 0);
			call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, block_d));
			call_block->getInstList ().push_back (call_l);
			unsigned position (0);
			for (auto i: call_a->elements)
            {
              auto element (llvm::ExtractValueInst::Create (call_l, position));
              call_block->getInstList ().push_back (element);
              auto real_element (llvm::PHINode::Create (element->getType (), 2));
              new_last->getInstList ().push_back (real_element);
              real_element->addIncoming (element, call_block);
              real_element->addIncoming (llvm::UndefValue::get (element->getType ()), last);
              i->generated = real_element;
              i->predicate = predicate;
              ++position;
            }
			break;
		}
		case mu::llvmc::skeleton::function_return_type::bmv0:
		{
			auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
			assert (call_a->elements.size () > 0);
			call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, block_d));
			call_block->getInstList ().push_back (call_l);
			auto real_call (llvm::PHINode::Create (call_l->getType(), 2));
			new_last->getInstList ().push_back (real_call);
			real_call->addIncoming (call_l, call_block);
			real_call->addIncoming (llvm::UndefValue::get (call_l->getType ()), last);
			unsigned position (0);
			auto selector_type (llvm::Type::getInt8Ty (context));
			for (auto k (call_a->elements.begin ()), l (call_a->elements.end ()); k != l; ++k)
            {
                auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, real_call, llvm::ConstantInt::get (selector_type, position)));
                new_last->getInstList ().push_back (compare);
                auto instruction (llvm::BinaryOperator::CreateAnd (predicate, compare));
                new_last->getInstList ().push_back (instruction);
                auto value (*k);
                value->generated = nullptr;
                value->predicate = instruction;
                ++position;
            }
			break;
		}
		case mu::llvmc::skeleton::function_return_type::bmvm:
		{
			auto call_l (llvm::CallInst::Create (function, llvm::ArrayRef <llvm::Value *> (arguments)));
			assert (call_a->elements.size () > 0);
			call_l->setDebugLoc (llvm::DebugLoc::get (call_a->elements [0]->region.first.row, call_a->elements [0]->region.first.column, block_d));
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
			auto current_element (call_a->elements.begin ());
			auto end_element (call_a->elements.end ());
			size_t current_selector (0);
			unsigned result_index (0);
			auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, selector, llvm::ConstantInt::get (selector_type, current_selector)));
			new_last->getInstList ().push_back (compare);
			auto instruction (llvm::BinaryOperator::CreateAnd (predicate, compare));
			new_last->getInstList ().push_back (instruction);
            for (auto & i: call_a->target->results.branches)
            {
                for (auto j: i.results)
                {
                    assert (current_element != end_element);
                    if (!j->type->is_unit_type ())
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
                }
                ++current_selector;
                compare = new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, selector, llvm::ConstantInt::get (selector_type, current_selector));
                new_last->getInstList ().push_back (compare);
                instruction = llvm::BinaryOperator::CreateAnd (predicate, compare);
                new_last->getInstList ().push_back (instruction);
            }
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
}

void mu::llvmc::generate_function::switch_element (mu::llvmc::skeleton::switch_element * element)
{
	assert (element->source->arguments.size () > 1);
	auto arg1 (mu::cast <mu::llvmc::skeleton::value> (element->source->arguments [1]));
	module.system.generate_value (arg1);
	llvm::Value * predicate (arg1->predicate);
	auto & elements (element->source->elements);
	size_t position (0);
	for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i, ++position)
	{
		auto value (*i);
		auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, arg1->generated, llvm::ConstantInt::get (arg1->generated->getType (), value->value_m->value_m)));
		last->getInstList().push_back (compare);
		auto switch_predicate (llvm::BinaryOperator::CreateAnd (predicate, compare));
		last->getInstList().push_back (switch_predicate);
		value->generated = nullptr;
		value->predicate = switch_predicate;
	}
	predicate = process_predicates (predicate, element->source->sequenced);
}

void mu::llvmc::generate_function::loop_element (mu::llvmc::skeleton::loop_element * loop_element)
{
	auto & context (module.system.result.module->getContext ());
	llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
	std::vector <llvm::PHINode *> parameters;
	auto phi_entry (llvm::BasicBlock::Create (context));
	auto shadow_entry (llvm::BasicBlock::Create (context));
	function_m->getBasicBlockList ().push_back (phi_entry);
	function_m->getBasicBlockList ().push_back (shadow_entry);
	{
		size_t position (0);
		for (auto i (loop_element->source->arguments.begin ()), j (loop_element->source->arguments.end ()); i < j; ++i, ++position)
		{
			auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
			module.system.generate_value (value);
			predicate = and_predicates (predicate, value->predicate);
			auto loop_parameter (llvm::PHINode::Create (value->generated->getType (), 2));
			loop_parameter->addIncoming (value->generated, last);
			phi_entry->getInstList ().push_back (loop_parameter);
			auto alloc (new llvm::AllocaInst (loop_parameter->getType ()));
			last->getInstList ().push_back (alloc);
			auto store (new llvm::StoreInst (loop_parameter, alloc));
			shadow_entry->getInstList ().push_back (store);
			assert (position < loop_element->source->parameters.size ());
			auto param (loop_element->source->parameters [position]);
			param->generated = loop_parameter;
			param->predicate = llvm::ConstantInt::getTrue (context);
			auto declaration (module.builder.insertDeclare (alloc, module.builder.createLocalVariable (llvm::dwarf::DW_TAG_auto_variable, function->debug, std::string (param->name.begin (), param->name.end ()), module.file, 0, param->type ()->debug), last));
			declaration->setDebugLoc (llvm::DebugLoc::get (value->region.first.row, value->region.first.column, function->debug));
			parameters.push_back (loop_parameter);
		}
		assert (position == loop_element->source->parameters.size ());
	}
	auto entry (last);
	auto successor (llvm::BasicBlock::Create (context));
	function_m->getBasicBlockList ().push_back (successor);
	entry->getInstList ().push_back (llvm::BranchInst::Create (phi_entry, successor, predicate));
	phi_entry->getInstList().push_back (llvm::BranchInst::Create (shadow_entry));
	last = shadow_entry;
	auto feedback_branch (true);
	auto branch_predicate (predicate);
	llvm::Value * feedback_predicate;
	size_t parameter_position (0);
	size_t element_position (0);
	auto empty (true);
    for (auto i (loop_element->source->results.begin ()), j (loop_element->source->results.end ()); i != j; ++i)
    {
        for (auto j (i->values.begin ()), k (i->values.end ()); j != k; ++j)
        {
			empty = false;
			auto value (*j);
			module.system.generate_value (value);
			branch_predicate = and_predicates (branch_predicate, value->predicate);
			if (feedback_branch)
			{
				assert (parameter_position < parameters.size ());
				parameters [parameter_position]->addIncoming (value->generated, last);
				++parameter_position;
			}
			else
			{
				auto real_value (llvm::PHINode::Create (value->generated->getType (), 2));
				real_value->addIncoming (llvm::UndefValue::get (value->generated->getType ()), last);
				real_value->addIncoming (value->generated, last);
				successor->getInstList ().push_back (real_value);
				parameters.push_back (real_value);
				auto real_predicate (llvm::PHINode::Create (value->predicate->getType (), 2));
				real_predicate->addIncoming (llvm::UndefValue::get (value->predicate->getType ()), last);
				real_predicate->addIncoming (value->predicate, last);
				successor->getInstList ().push_back (real_predicate);
				parameters.push_back (real_predicate);
				assert (element_position < loop_element->source->elements.size ());
				loop_element->source->elements [element_position]->generated = real_value;
				loop_element->source->elements [element_position]->predicate = real_predicate;
				++element_position;
			}
        }
        for (auto j (i->sequenced.begin ()), k (i->sequenced.end ()); j != k; ++j)
        {
            auto value (*j);
			module.system.generate_value (value);
			branch_predicate = and_predicates (branch_predicate, value->predicate);
        }
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
            loop_element->source->elements [element_position]->generated = nullptr;
            loop_element->source->elements [element_position]->predicate = real_predicate;
            ++element_position;
        }
        empty = true;
        branch_predicate = predicate;
    }
	for (auto i: parameters)
	{
		i->setIncomingBlock (0, entry);
		i->setIncomingBlock (1, last);
	}
	auto feedback (llvm::BranchInst::Create (phi_entry, successor, feedback_predicate));
	last->getInstList ().push_back (feedback);
	last = successor;
}

void mu::llvmc::generate_function::identity_element (mu::llvmc::skeleton::identity_element * identity_value)
{
	auto i (identity_value->source->arguments.begin () + 1);
	auto j (identity_value->source->arguments.end ());
	auto k (identity_value->source->elements.begin ());
	auto l (identity_value->source->elements.end ());
	for (; i != j; ++i, ++k)
	{
		assert (k != l);
		auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
		module.system.generate_value (value);
		auto target (*k);
		target->predicate = value->predicate;
		target->generated = value->generated;
	}
	assert ((i == j) == (k == l));
	auto m (identity_value->source->arguments.end ());
	for (; i != m; ++i)
	{
		auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
		module.system.generate_value (value);
	}
}

void mu::llvmc::generate_module::constant_aggregate_zero (mu::llvmc::skeleton::constant_aggregate_zero * node_a)
{
	auto type (node_a->type ());
	system.generate_type (type);
	node_a->predicate = llvm::ConstantInt::getTrue (system.result.module->getContext ());
	node_a->generated = llvm::ConstantAggregateZero::get (type->generated);
}

void mu::llvmc::generate_function::join_element (mu::llvmc::skeleton::join_element * join)
{
	auto & branches (join->source->branches);
	assert (branches.size () > 1);
	for (auto & i: branches)
	{
		llvm::Value * predicate (llvm::ConstantInt::getTrue (function_m->getContext ()));
		for (auto j: i.arguments)
		{
			module.system.generate_value (j);
			predicate = and_predicates (predicate, j->predicate);
		}
		for (auto j: i.predicates)
		{
			module.system.generate_value (j);
			predicate = and_predicates (predicate, j->predicate);
		}
		i.predicate = predicate;
	}
	for (size_t i (0), j (branches [0].arguments.size ()); i < j; ++i)
	{
		assert (join->source->elements.size () > i);
		assert (branches [0].arguments.size () > i);
		auto first (branches [0].arguments [i]);
		auto type (first->type ());
		auto unit (type->is_unit_type ());
		llvm::Value * predicate (llvm::ConstantInt::getFalse (function_m->getContext ()));
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
		for (auto & k: branches)
		{
			assert (k.arguments.size () > i);
			assert (k.predicate != nullptr);
			auto value_l (k.arguments [i]);
			assert (value_l->predicate != nullptr);
			auto predicate_instruction (llvm::BinaryOperator::CreateOr (predicate, k.predicate));
			last->getInstList ().push_back (predicate_instruction);
			if (!unit)
			{
				auto select_instruction (llvm::SelectInst::Create (k.predicate, value_l->generated, value));
				last->getInstList ().push_back (select_instruction);
				value = select_instruction;
			}
			predicate = predicate_instruction;
			join->source->elements [i]->predicate = predicate;
			join->source->elements [i]->generated = value;
		}
	}
}

void mu::llvmc::generate_module::unit_value (mu::llvmc::skeleton::unit_value * node_a)
{
	node_a->generated = nullptr;
	node_a->predicate = llvm::ConstantInt::getTrue (system.result.module->getContext ());
}

void mu::llvmc::generate_function::inline_asm (mu::llvmc::skeleton::inline_asm * asm_l)
{
	assert (asm_l->arguments.size () > 0);
	assert (dynamic_cast <mu::llvmc::skeleton::asm_c *> (asm_l->arguments [0]) != nullptr);
	auto info (static_cast <mu::llvmc::skeleton::asm_c *> (asm_l->arguments [0]));
	auto & context (module.system.result.module->getContext ());
	llvm::Value * predicate (llvm::ConstantInt::getTrue (context));
	std::vector <llvm::Type *> types;
	std::vector <llvm::Value *> arguments;
	for (auto i (asm_l->arguments.begin () + 1), j (asm_l->arguments.end ()); i < j; ++i)
	{
		auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
		module.system.generate_value (value);
		predicate = and_predicates (predicate, value->predicate);
		if (value->generated != nullptr)
		{
			arguments.push_back (value->generated);
			types.push_back (value->generated->getType ());
		}
	}
	for (auto i (asm_l->sequenced.begin ()), j (asm_l->sequenced.end ()); i < j; ++i)
	{
		auto value (mu::cast <mu::llvmc::skeleton::value> (*i));
		module.system.generate_value (value);
		predicate = and_predicates (predicate, value->predicate);
	}
	llvm::Type * type;
	if (!info->type_m->is_unit_type ())
	{
		module.system.generate_type (info->type_m);
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
	function_m->getBasicBlockList ().push_back (call_block);
	auto successor (llvm::BasicBlock::Create (context));
	function_m->getBasicBlockList ().push_back (successor);
	auto predicate_branch (llvm::BranchInst::Create (call_block, successor, predicate));
	last->getInstList ().push_back (predicate_branch);
	call_block->getInstList ().push_back (call);
	auto rejoin (llvm::BranchInst::Create (successor));
	call_block->getInstList ().push_back (rejoin);
	llvm::Value * value;
	if (!info->type_m->is_unit_type ())
	{
		value = generate_rejoin (last, call_block, successor, call);
	}
	else
	{
		value = nullptr;
	}
	asm_l->generated = value;
	asm_l->predicate = predicate;
	last = successor;
}

void mu::llvmc::generate_function::named (mu::llvmc::skeleton::named * named)
{
	auto value_l (named->value_m);
	module.system.generate_value (value_l);
	named->generated = value_l->generated;
	named->predicate = value_l->predicate;
	auto const & name (named->name);
	auto type (named->type ());
	module.system.generate_type (type);
	assert (type->generated != nullptr);
	if (value_l->generated != nullptr)
	{
		auto alloc (new llvm::AllocaInst (named->generated->getType ()));
		last->getInstList ().push_back (alloc);
		auto store (new llvm::StoreInst (named->generated, alloc));
		last->getInstList().push_back (store);
		auto variable_info (module.builder.createLocalVariable (llvm::dwarf::DW_TAG_auto_variable, function->debug, std::string (name.begin (), name.end ()), module.file, named->region.first.row, type->debug));
		auto declaration (module.builder.insertDeclare (alloc, variable_info, last));
		declaration->setDebugLoc (llvm::DebugLoc::get (named->region.first.row, named->region.first.column, function->debug));
		auto update (module.builder.insertDbgValueIntrinsic(named->generated, 0, variable_info, last));
		update->setDebugLoc (llvm::DebugLoc::get (named->region.first.row, named->region.first.column, function->debug));
	}
}

void mu::llvmc::generate_function::instruction (mu::llvmc::skeleton::instruction * instruction)
{
	llvm::Value * predicate;
	llvm::Value * value;
	auto & context (module.system.result.module->getContext ());
	switch (instruction->marker ())
	{
		case mu::llvmc::instruction_type::add:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateAdd (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::and_i:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateAnd (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::alloca:
		{
			assert (instruction->arguments.size () == 2);
			assert (dynamic_cast <mu::llvmc::skeleton::type *> (instruction->arguments [1]) != nullptr);
			auto type (static_cast <mu::llvmc::skeleton::type *> (instruction->arguments [1]));
			module.system.generate_type (type);
			predicate = llvm::ConstantInt::getTrue (module.system.result.module->getContext ());
			predicate = process_predicates (predicate, instruction->sequenced);
			auto predicate_branch (llvm::BasicBlock::Create (context));
			function_m->getBasicBlockList().push_back (predicate_branch);
			auto new_last (llvm::BasicBlock::Create (context));
			function_m->getBasicBlockList().push_back (new_last);
			last->getInstList ().push_back (llvm::BranchInst::Create (predicate_branch, new_last, predicate));
			auto instruction_l (new llvm::AllocaInst (type->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			predicate_branch->getInstList ().push_back (instruction_l);
			predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
			value = generate_rejoin (last, predicate_branch, new_last, instruction_l);
			last = new_last;
			break;
		}
		case mu::llvmc::instruction_type::ashr:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateAShr (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::bitcast:
		{
			assert (instruction->arguments.size () == 3);
			auto value_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (value_l);
			auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
			module.system.generate_type (type_l);
			predicate = value_l->predicate;
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BitCastInst::CreatePointerCast (value_l->generated, type_l->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::cmpxchg:
		{
			assert (instruction->arguments.size () == 4);
			auto one (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (one);
			auto two (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (two);
			auto three (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [3]));
			module.system.generate_value (three);
			predicate = and_predicates (one->predicate, two->predicate);
			predicate = and_predicates (predicate, three->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto predicate_branch (llvm::BasicBlock::Create (context));
			function_m->getBasicBlockList().push_back (predicate_branch);
			auto new_last (llvm::BasicBlock::Create (context));
			function_m->getBasicBlockList().push_back (new_last);
			last->getInstList ().push_back (llvm::BranchInst::Create (predicate_branch, new_last, predicate));
			auto instruction_l (new llvm::AtomicCmpXchgInst (one->generated, two->generated, three->generated, llvm::AtomicOrdering::AcquireRelease, llvm::SynchronizationScope::CrossThread));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			predicate_branch->getInstList ().push_back (instruction_l);
			predicate_branch->getInstList ().push_back (llvm::BranchInst::Create(new_last));
			value = generate_rejoin (last, predicate_branch, new_last, instruction_l);
			last = new_last;
			break;
		}
		case mu::llvmc::instruction_type::extractvalue:
		{
			assert (instruction->arguments.size () == 3);
			auto aggregate (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (aggregate);
			auto index (mu::cast <mu::llvmc::skeleton::constant_integer> (instruction->arguments [2]));
			module.system.generate_value (index);
			predicate = and_predicates (aggregate->predicate, index->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::ExtractValueInst::Create (aggregate->generated, llvm::ArrayRef <unsigned> (index->value_m)));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::getelementptr:
		{
			assert (instruction->arguments.size () >= 3);
			auto one (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (one);
			auto two (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (two);
			predicate = and_predicates (one->predicate, two->predicate);
			std::vector <llvm::Value *> indicies;
			indicies.push_back (two->generated);
			for (auto i (instruction->arguments.begin () + 3), j (instruction->arguments.end ()); i != j; ++i)
			{
				auto trailing (mu::cast <mu::llvmc::skeleton::constant_integer> (*i));
				module.system.generate_value (trailing);
				indicies.push_back (trailing->generated);
			}
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::GetElementPtrInst::CreateInBounds (one->generated, llvm::ArrayRef <llvm::Value *> (indicies)));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::icmp:
		{
			assert (false);
		}
		case mu::llvmc::instruction_type::insertvalue:
		{
			assert (instruction->arguments.size () >= 4);
			auto struct_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (struct_l);
			auto value_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (value_l);
			std::vector <unsigned> indicies;
			for (auto i (instruction->arguments.begin () + 3), j (instruction->arguments.end ()); i != j; ++i)
			{
				auto constant (mu::cast <mu::llvmc::skeleton::constant_integer> (*i));
				indicies.push_back (constant->value_m);
			}
			predicate = struct_l->predicate;
			predicate = and_predicates (predicate, value_l->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::InsertValueInst::Create (struct_l->generated, value_l->generated, llvm::ArrayRef <unsigned> (indicies)));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::inttoptr:
		{
			assert (instruction->arguments.size () == 3);
			auto value_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (value_l);
			auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
			module.system.generate_type (type_l);
			predicate = value_l->predicate;
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (new llvm::IntToPtrInst (value_l->generated, type_l->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::load:
		{
			assert (instruction->arguments.size () == 2);
			auto load_pointer (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (load_pointer);
			predicate = process_predicates (load_pointer->predicate, instruction->sequenced);
			auto predicate_branch (llvm::BasicBlock::Create (context));
			function_m->getBasicBlockList ().push_back (predicate_branch);
			auto new_last (llvm::BasicBlock::Create (context));
			function_m->getBasicBlockList ().push_back (new_last);
			last->getInstList ().push_back (llvm::BranchInst::Create (predicate_branch, new_last, predicate));
			auto instruction_l (new llvm::LoadInst (load_pointer->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, block_d));
			predicate_branch->getInstList ().push_back (instruction_l);
			predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
			value = generate_rejoin (last, predicate_branch, new_last, instruction_l);
			last = new_last;
			break;
		}
		case mu::llvmc::instruction_type::lshr:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateLShr (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::mul:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateMul (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::or_i:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateOr (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::ptrtoint:
		{
			assert (instruction->arguments.size () == 3);
			auto value_l (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (value_l);
			auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
			module.system.generate_type (type_l);
			predicate = value_l->predicate;
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::PtrToIntInst::CreatePointerCast (value_l->generated, type_l->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::sdiv:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateSDiv (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::select:
		{
			assert (instruction->arguments.size () == 4);
			auto condition (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (condition);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [3]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::SelectInst::Create(condition->generated, left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::sext:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto type_l (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
			module.system.generate_type (type_l);
			predicate = process_predicates (left->predicate, instruction->sequenced);
			auto instruction_l (llvm::SExtInst::CreateSExtOrBitCast (left->generated, type_l->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::shl:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateShl (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::srem:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateSRem (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::store:
		{
			assert (false);
		}
		case mu::llvmc::instruction_type::sub:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateSub (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, block_d));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::udiv:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateUDiv (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, block_d));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::urem:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateURem (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, block_d));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::xor_i:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [2]));
			module.system.generate_value (right);
			predicate = and_predicates (left->predicate, right->predicate);
			predicate = process_predicates (predicate, instruction->sequenced);
			auto instruction_l (llvm::BinaryOperator::CreateXor (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, block_d));
			last->getInstList ().push_back (instruction_l);
			value = instruction_l;
			break;
		}
		case mu::llvmc::instruction_type::zext:
		{
			assert (instruction->arguments.size () == 3);
			auto left (mu::cast <mu::llvmc::skeleton::value> (instruction->arguments [1]));
			module.system.generate_value (left);
			auto right (mu::cast <mu::llvmc::skeleton::type> (instruction->arguments [2]));
			module.system.generate_type (right);
			predicate = process_predicates (left->predicate, instruction->sequenced);
			auto instruction_l (llvm::SExtInst::CreateZExtOrBitCast (left->generated, right->generated));
			instruction_l->setDebugLoc (llvm::DebugLoc::get (instruction->region.first.row, instruction->region.first.column, function->debug));
			last->getInstList ().push_back (instruction_l);
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

void mu::llvmc::generate_function::icmp (mu::llvmc::skeleton::icmp * icmp)
{
	module.system.generate_value (icmp->left);
	module.system.generate_value (icmp->right);
	auto predicate (and_predicates (icmp->left->predicate, icmp->right->predicate));
	predicate = process_predicates (predicate, icmp->sequenced);
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
	instruction_l->setDebugLoc (llvm::DebugLoc::get (icmp->region.first.row, icmp->region.first.column, block_d));
	last->getInstList ().push_back (instruction_l);
	icmp->generated = instruction_l;
	icmp->predicate = predicate;
}

void mu::llvmc::generate_function::store (mu::llvmc::skeleton::store * store)
{
	module.system.generate_value (store->source);
	module.system.generate_value (store->destination);
	auto predicate (and_predicates (store->destination->predicate, store->source->predicate));
	predicate = process_predicates (predicate, store->sequenced);
	auto & context (module.system.result.module->getContext ());
	auto predicate_branch (llvm::BasicBlock::Create (context));
	function_m->getBasicBlockList ().push_back (predicate_branch);
	auto new_last (llvm::BasicBlock::Create (context));
	function_m->getBasicBlockList ().push_back (new_last);
	last->getInstList ().push_back (llvm::BranchInst::Create(predicate_branch, new_last, predicate));
	auto instruction_l (new llvm::StoreInst (store->source->generated, store->destination->generated));
	instruction_l->setDebugLoc (llvm::DebugLoc::get (store->region.first.row, store->region.first.column, block_d));
	predicate_branch->getInstList ().push_back (instruction_l);
	predicate_branch->getInstList ().push_back (llvm::BranchInst::Create (new_last));
	store->generated = nullptr;
	store->predicate = predicate;
	last = new_last;
}

void mu::llvmc::generate_system::generate_value (mu::llvmc::skeleton::value * node_a)
{
    assert (node_a != nullptr);
    if (node_a->predicate == nullptr)
    {
        node_a->visit (current_generator);
    }
    assert (node_a->predicate != nullptr);
}

llvm::Value * mu::llvmc::generate_function::process_predicates (llvm::Value * predicate_a, mu::vector <mu::llvmc::skeleton::value *> const & sequenced_a)
{
    llvm::Value * predicate (predicate_a);
    for (auto i (sequenced_a.begin ()), j (sequenced_a.end ()); i < j; ++i)
    {
        auto value_l (*i);
        module.system.generate_value (value_l);
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

void mu::llvmc::generate_module::constant_array (mu::llvmc::skeleton::constant_array * constant_array)
{
	std::vector <llvm::Constant *> elements;
	for (auto i: constant_array->initializer)
	{
		system.generate_value (i);
		elements.push_back (llvm::cast <llvm::Constant> (i->generated));
	}
	auto type (constant_array->type ());
	system.generate_type (type);
	constant_array->generated = llvm::ConstantArray::get (llvm::cast <llvm::ArrayType> (type->generated), llvm::ArrayRef <llvm::Constant *> (elements));
	constant_array->predicate = llvm::ConstantInt::getTrue (system.result.module->getContext ());
}

void mu::llvmc::generate_module::constant_pointer_null (mu::llvmc::skeleton::constant_pointer_null * value_a)
{
	auto type (value_a->type ());
	system.generate_type (type);
	value_a->predicate = llvm::ConstantInt::getTrue (system.result.module->getContext ());
	value_a->generated = llvm::ConstantPointerNull::get(llvm::cast <llvm::PointerType> (type->generated));
}

void mu::llvmc::generate_module::constant_integer (mu::llvmc::skeleton::constant_integer * constant_int)
{
	auto type (constant_int->type ());
	system.generate_type (type);
	constant_int->predicate = llvm::ConstantInt::getTrue (system.result.module->getContext ());
	constant_int->generated = llvm::ConstantInt::get (type->generated, constant_int->value_m);
}

void mu::llvmc::generate_module::global_variable (mu::llvmc::skeleton::global_variable * global_variable)
{
	system.generate_value (global_variable->initializer);
	auto type (global_variable->initializer->type ());
	system.generate_type (type);
	auto global (new llvm::GlobalVariable (type->generated, false, llvm::GlobalValue::LinkageTypes::ExternalLinkage, llvm::cast <llvm::Constant> (global_variable->initializer->generated)));
	global->setName (get_global_name (global_variable->name));
	auto global_type (global_variable->type ());
	system.generate_type (global_type);
	global_variable->debug = builder.createGlobalVariable (std::string (global_variable->name.begin (), global_variable->name.end ()), file, global_variable->region.first.row, global_type->debug, false, global);
	global_variable->generated = global;
	global_variable->predicate = global_variable->initializer->predicate;
	system.result.module->getGlobalList ().push_back (global);
}

void mu::llvmc::generate_module::undefined (mu::llvmc::skeleton::undefined * node_a)
{
	auto type (node_a->type ());
	system.generate_type (type);
	auto generated (llvm::UndefValue::get (type->generated));
	node_a->generated = generated;
	node_a->predicate = llvm::ConstantInt::getTrue (system.result.module->getContext ());
}

void mu::llvmc::generate_module::function (mu::llvmc::skeleton::function * node_a)
{
	auto type (&node_a->type_m);
	system.generate_type (type);
	auto function_type (llvm::cast <llvm::FunctionType> (type->generated));
	auto function_l (llvm::Function::Create (function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage));
	function_l->setName (get_global_name (node_a->name));
	node_a->debug = builder.createFunction (file, std::string (node_a->name.begin (), node_a->name.end ()), function_l->getName (), file, node_a->region.first.row, type->debug, false, true, node_a->region.first.row, 0, false, function_l);
	system.result.module->getFunctionList ().push_back (function_l);
	node_a->generated = function_l;
	node_a->predicate = llvm::ConstantInt::getTrue (function_type->getContext ());
	mu::llvmc::generate_function generator_l (*this, node_a);
	generator_l.generate ();
}

void mu::llvmc::generate_module::named (mu::llvmc::skeleton::named * node_a)
{
	system.generate_value (node_a->value_m);
	assert (dynamic_cast <mu::llvmc::skeleton::global_value *> (node_a->value_m) == nullptr && "Global values should have their name members assigned");
	node_a->predicate = node_a->value_m->predicate;
	node_a->generated = node_a->value_m->generated;
}

std::string mu::llvmc::generate_module::get_global_name (mu::string const & name_a)
{
	std::string name;
	char buffer [32];
	sprintf (buffer, "%016" PRIx64, system.module_id);
	name.append (buffer);
	name.push_back ('-');
	sprintf (buffer, "%016" PRIx64, global_id++);
	name.append (buffer);
	name.push_back ('-');
	name += std::string (name_a.begin (), name_a.end ());
	return name;
}

llvm::Value * mu::llvmc::generate_function::and_predicates (llvm::Value * left_a, llvm::Value * right_a)
{
    auto and_instruction (llvm::BinaryOperator::CreateAnd (left_a, right_a));
    last->getInstList ().push_back (and_instruction);
    return and_instruction;
}

void mu::llvmc::generate_system::generate_type (mu::llvmc::skeleton::type * type_a)
{
    if (type_a->generated == nullptr)
    {
		type_a->visit (current_generator);
    }
    assert (type_a->generated != nullptr);
    assert (type_a->debug.isValid ());
}

void mu::llvmc::generate_module::integer_type (mu::llvmc::skeleton::integer_type * integer_type)
{
	integer_type->generated = llvm::Type::getIntNTy (system.result.module->getContext (), integer_type->bits);
	std::string name ("int");
	char buffer [32];
	sprintf (buffer, "%d", static_cast <int> (integer_type->bits));
	name.append (buffer);
	integer_type->debug = builder.createBasicType (name, integer_type->bits, 0, llvm::dwarf::DW_ATE_unsigned);
}

void mu::llvmc::generate_module::pointer_type (mu::llvmc::skeleton::pointer_type * pointer_type)
{
	auto element_type (pointer_type->pointed_type);
	system.generate_type (element_type);
	assert (element_type->generated != nullptr);
	assert (element_type->debug != nullptr);
	pointer_type->debug = builder.createPointerType (element_type->debug, 8, 0, "ptr");
	pointer_type->generated = llvm::PointerType::get (element_type->generated, 0);
}

void mu::llvmc::generate_module::unit_type (mu::llvmc::skeleton::unit_type * unit_type)
{
	unit_type->generated = llvm::Type::getVoidTy (system.result.module->getContext ());
	unit_type->debug = builder.createBasicType ("unit", 0, 0, llvm::dwarf::DW_ATE_unsigned_char);
}

void mu::llvmc::generate_module::function_type (mu::llvmc::skeleton::function_type * function_type_a)
{
	auto & context (system.result.module->getContext ());
	auto function (function_type_a->function);
	std::vector <llvm::Value *> function_type_values;
	function_type_values.push_back (nullptr); // Return type
	std::vector <llvm::Type *> parameters;
	for (auto i (function->parameters.begin ()), j (function->parameters.end ()); i != j; ++i)
	{
		auto parameter (*i);
		auto type_s (parameter->type ());
		system.generate_type (type_s);
		function_type_values.push_back (type_s->debug);
		parameters.push_back (type_s->generated);
	}
	std::vector <llvm::Value *> results_debug;
	std::vector <llvm::Type *> results;
	uint64_t offset (0);
    for (auto & i: function->results.branches)
    {
        for (auto j: i.results)
        {
            auto type_s (j->type);
            if (!type_s->is_unit_type())
            {
                system.generate_type (type_s);
                auto size (type_s->debug.getSizeInBits ());
                auto line (type_s->debug.getLineNumber ());
                auto member (builder.createMemberType (file, "", file, line, size, 0, offset, 0, type_s->debug));
                results_debug.push_back (member);
                results.push_back (type_s->generated);
                offset += size;
            }
        }
    }
	if (function->results.size () > 1)
	{
		results.push_back (llvm::Type::getInt8Ty (context));
		results_debug.push_back (builder.createBasicType ("int8", 8, 0, llvm::dwarf::DW_ATE_unsigned_char));
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
			auto array (builder.getOrCreateArray (llvm::ArrayRef <llvm::Value *> (results_debug)));
			result_type_debug = builder.createStructType (file, "", file, function->region.first.row, offset, 0, 0, array);
		}
	}
	function_type_values [0] = result_type_debug;
	auto function_type (llvm::FunctionType::get (result_type, llvm::ArrayRef <llvm::Type *> (parameters), false));
	auto array (builder.getOrCreateArray (llvm::ArrayRef <llvm::Value *> (function_type_values)));
	auto function_type_d (builder.createSubroutineType (file, array));
	function_type_a->generated = function_type;
	function_type_a->debug = function_type_d;
}

void mu::llvmc::generate_module::fixed_array_type (mu::llvmc::skeleton::fixed_array_type * array_type)
{
	auto & context (system.result.module->getContext ());
	auto type (array_type->element);
	system.generate_type (type);
	array_type->generated = llvm::ArrayType::get (type->generated, array_type->size);
	llvm::Value * indicies [2] = {llvm::ConstantInt::get(llvm::Type::getInt64Ty (context), 0), llvm::ConstantInt::get(llvm::Type::getInt64Ty (context), array_type->size)};
	array_type->debug = builder.createArrayType (array_type->size, 0, type->debug, builder.getOrCreateArray(llvm::ArrayRef <llvm::Value *> (indicies)));
}

void mu::llvmc::generate_module::struct_type (mu::llvmc::skeleton::struct_type * struct_type)
{
	auto & context (system.result.module->getContext ());
	std::vector <llvm::Type *> elements;
	std::vector <llvm::Value *> debug_members;
	size_t offset (0);
	for (auto i: struct_type->elements)
	{
		i->visit (this);
		elements.push_back (i->generated);
		auto size (i->debug.getSizeInBits ());
		auto member (builder.createMemberType (file, "", file, 0, size, 0, offset, 0, i->debug));
		offset += size;
		debug_members.push_back (member);
	}
	auto type (llvm::StructType::get (context, elements));
	auto debug (builder.createStructType (file, "", file, 0, offset, 0, 0, builder.getOrCreateArray (debug_members)));
	struct_type->generated = type;
	struct_type->debug = debug;
}

mu::llvmc::generate_system::generate_system (llvm::LLVMContext & context_a, mu::string const & name_a, mu::string const & path_a, uint64_t module_id_a) :
current_generator (this),
name (name_a),
path (path_a),
module_id (module_id_a),
result ({nullptr, nullptr})
{
	char id [32];
	sprintf (id, "%016" PRIx64 "", module_id_a);
	result.module = new llvm::Module (id, context_a);
}

void mu::llvmc::generate_function::node (mu::llvmc::skeleton::node * node_a)
{
	node_a->visit (&module);
}

void mu::llvmc::generate_module::node (mu::llvmc::skeleton::node * node_a)
{
	node_a->visit (&system);
}