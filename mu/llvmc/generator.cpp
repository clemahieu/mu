#include <mu/llvmc/generator.hpp>

#include <mu/llvmc/ast.hpp>
#include <mu/core/error_string.hpp>
#include <mu/llvmc/skeleton.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>

#include <boost/array.hpp>

#include <gc_cpp.h>

#include <algorithm>

llvm::Module * mu::llvmc::generator::generate (llvm::LLVMContext & context_a, mu::llvmc::skeleton::module * module_a)
{
    auto module (new llvm::Module ("", context_a));
    mu::llvmc::generate_module generator (module_a, module);
    generator.generate ();
    return module;
}

mu::llvmc::generate_module::generate_module (mu::llvmc::skeleton::module * module_a, llvm::Module * target_a) :
module (module_a),
target (target_a)
{
}

void mu::llvmc::generate_module::generate ()
{
    for (auto i (module->functions.begin ()), j (module->functions.end ()); i != j; ++i)
    {
        mu::llvmc::generate_function generator_l (*this, *i);
        generator_l.generate ();
    }
}

mu::llvmc::generate_function::generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a) :
module (module_a),
unreachable (llvm::BasicBlock::Create (module.target->getContext ())),
function (function_a),
function_return_type (get_return_type (function_a))
{
    auto entry_block (new (GC) mu::llvmc::block (0, nullptr));
    entry_block->instructions = llvm::BasicBlock::Create (module.target->getContext ());
    entry_block->phis = llvm::BasicBlock::Create (module.target->getContext ());
    auto entry_branch (new (GC) mu::llvmc::branch (entry_block, entry_block, nullptr, nullptr));
    entry_branch->first = entry_block;
    entry_branch->last = entry_block;
    entry_branch->parent = nullptr;
    entry_branch->test = nullptr;
    entry_block->branch = entry_branch;
    unreachable->getInstList ().push_back (new llvm::UnreachableInst (module.target->getContext ()));
}

mu::llvmc::function_return_type mu::llvmc::generate_function::get_return_type (mu::llvmc::skeleton::function * function_a)
{
    mu::llvmc::function_return_type result;
    size_t llvm_values (0);
    for (auto i (function_a->results.begin ()), j (function_a->results.end ()); i != j && llvm_values < 2; ++i)
    {
        if (!(*i)->type->is_bottom_type ())
        {
            ++llvm_values;
        }
    }
    switch (function_a->branch_offsets.size ())
    {
        case 0:
            result = mu::llvmc::function_return_type::b0;
            break;
        case 1:
        {
            switch (llvm_values)
            {
                case 0:
                    result = mu::llvmc::function_return_type::b1v0;
                    break;
                case 1:
                    result = mu::llvmc::function_return_type::b1v1;
                    break;
                default:
                    result = mu::llvmc::function_return_type::b1vm;
                    break;
            }
            break;
        }
        default:
        {
            switch (llvm_values)
            {
                case 0:
                    result = mu::llvmc::function_return_type::bmv0;
                    break;
                default:
                    result = mu::llvmc::function_return_type::bmvm;
                    break;
            }
            break;
        }
    }
    return result;
}

void mu::llvmc::generate_function::generate ()
{
    std::vector <llvm::Type *> parameters;
    for (auto i (function->parameters.begin ()), j (function->parameters.end ()); i != j; ++i)
    {
        auto parameter (*i);
        auto type_l (generate_type (parameter->type ()));
        parameters.push_back (type_l);
    }
    std::vector <llvm::Type *> results;
    for (size_t i (0), j (function->branch_offsets.size ()); i != j; ++i)
    {
        for (auto k (function->branch_begin (i)), l (function->branch_end (i)); k != l; ++k)
        {
            auto type_s ((*k)->type);
            if (!type_s->is_bottom_type())
            {
                auto type_l (generate_type (type_s));
                results.push_back (type_l);
            }
        }
    }
    if (function->branch_offsets.size () > 1)
    {
        results.push_back (llvm::Type::getInt8Ty (module.target->getContext ()));
    }
    llvm::Type * result_type;
    switch (results.size ())
    {
        case 0:
            result_type = llvm::Type::getVoidTy (module.target->getContext ());
            break;
        case 1:
            result_type = results [0];
            break;
        default:
        {
            result_type = llvm::StructType::create (module.target->getContext(), llvm::ArrayRef <llvm::Type *> (results));
        }
    }
    auto function_type (llvm::FunctionType::get (result_type, llvm::ArrayRef <llvm::Type *> (parameters), false));
    auto function_l (llvm::Function::Create (function_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage));
    {
        auto i (function_l->arg_begin());
        auto j (function_l->arg_end());
        auto k (function->parameters.begin ());
        auto l (function->parameters.end ());
        for (; i != j; ++i, ++k)
        {
            assert (k != l);
            llvm::Value * parameter (i);
            already_generated [*k] = new (GC) mu::llvmc::value_data ({body->first, parameter});
        }
        assert ((i != j) == (k != l));
    }
    function_m = function_l;
    function_l->getBasicBlockList ().push_back (body->first->phis);
    function_l->getBasicBlockList ().push_back (body->first->instructions);
    function_l->getBasicBlockList ().push_back (unreachable);
    module.target->getFunctionList ().push_back (function_l);
    assert (module.functions.find (function) == module.functions.end ());
    module.functions [function] = function_l;
    if (function->results.empty ())
    {
        function_l->addFnAttr (llvm::Attributes::NoReturn);
    }
    for (auto i: function->results)
    {
        auto value_l (pull_value (body, i->value));
    }
    assert (false); // Execute terminators, return
}

mu::llvmc::terminator_return::terminator_return (mu::llvmc::generate_function & generator_a) :
generator (generator_a)
{
}

void mu::llvmc::terminator_return::terminate (llvm::BasicBlock * block_a)
{
    /*auto index_l (generator.terminating_branch);
    generator.terminating_branch = index_l + 1;
    switch (generator.function_return_type)
    {
        case mu::llvmc::function_return_type::b0:
            block_a->getInstList ().push_back (new llvm::UnreachableInst (block_a->getContext()));
            break;
        case mu::llvmc::function_return_type::b1v0:
            block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext ()));
            break;
        case mu::llvmc::function_return_type::b1v1:
        {
            auto value_l (generator.already_generated [generator.function->results [0]->value]);
            block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext (), value_l.value));
            break;
        }
        case mu::llvmc::function_return_type::b1vm:
        {
            auto result_type (generator.function_m->getReturnType ());
            llvm::Value * result_value (llvm::UndefValue::get (result_type));
            {
                auto k (generator.function->branch_offsets [index_l]);
                for (auto i (generator.function->branch_begin (index_l)), j (generator.function->branch_end (index_l)); i != j; ++i, ++k)
                {
                    assert (generator.already_generated.find ((*i)->value) != generator.already_generated.end ());
                    auto value (*i);
                    if (!value->type->is_bottom_type ())
                    {
                        auto generated (generator.already_generated [(*i)->value].value);
                        auto inst (llvm::InsertValueInst::Create (result_value, generated, llvm::ArrayRef <unsigned> (k)));
                        block_a->getInstList ().push_back (inst);
                        result_value = inst;
                    }
                }
            }
            block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext (), result_value));
            break;
        }
        case mu::llvmc::function_return_type::bmv0:
        {
            assert (generator.function->branch_offsets.size () > index_l);
            auto selector (llvm::ConstantInt::get (llvm::Type::getInt8Ty (generator.function_m->getContext ()), index_l));
            block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext (), selector));
            break;
        }
        case mu::llvmc::function_return_type::bmvm:
        {
            assert (generator.function->branch_offsets.size () > index_l);
            auto selector (llvm::ConstantInt::get (llvm::Type::getInt8Ty (generator.function_m->getContext ()), index_l));
            auto result_type (llvm::cast <llvm::StructType> (generator.function_m->getReturnType ()));
            llvm::Value * result_value (llvm::UndefValue::get (result_type));
            {
                auto k (generator.branch_offsets [index_l]);
                for (auto i (generator.function->branch_begin (index_l)), j (generator.function->branch_end (index_l)); i != j; ++i)
                {
                    assert (generator.already_generated.find ((*i)->value) != generator.already_generated.end ());
                    auto value (*i);
                    if (!value->type->is_bottom_type ())
                    {
                        auto generated (generator.already_generated [(*i)->value].value);
                        auto type1 (result_type->getTypeAtIndex (k));
                        auto type2 (generated->getType ());
                        assert (type1 == type2);
                        auto inst (llvm::InsertValueInst::Create (result_value, generated, llvm::ArrayRef <unsigned> (k)));
                        block_a->getInstList ().push_back (inst);
                        result_value = inst;
                        ++k;
                    }
                }
            }
            auto inst (llvm::InsertValueInst::Create (result_value, selector, llvm::ArrayRef <unsigned> (llvm::cast <llvm::StructType> (result_type)->getNumElements () - 1)));
            block_a->getInstList ().push_back (inst);
            result_value = inst;
            block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext (), result_value));
            break;
        }
        default:
            assert (false);
            break;
    }*/
}

mu::llvmc::block::block (size_t order_a, llvm::TerminatorInst * terminator_a) :
order (order_a),
terminator (terminator_a)
{
}

mu::llvmc::block::block (size_t order_a, llvm::TerminatorInst * terminator_a, mu::llvmc::branch * branch_a) :
branch (branch_a),
order (order_a),
terminator (terminator_a)
{    
}

mu::llvmc::value_data * mu::llvmc::generate_function::pull_value (mu::llvmc::branch * branch_a, mu::llvmc::skeleton::value * value_a)
{
    auto result (retrieve_value (value_a));
    while (result->block->branch != branch_a)
    {
        auto destination (result->block->branch->last);
        auto phi (llvm::PHINode::Create (result->value->getType (), destination->predecessors.size ()));
        for (auto & i: destination->predecessors)
        {
            if (i == result->block)
            {
                phi->addIncoming (result->value, result->block->instructions);
            }
            else
            {
                phi->addIncoming (llvm::UndefValue::get (result->value->getType ()), result->block->instructions);
            }
        }
        destination->phis->getInstList ().push_back (phi);
        auto new_result (new (GC) mu::llvmc::value_data ({destination, phi, nullptr}));
        result->forward_value = new_result;
        result = new_result;
    }
    return result;
}

mu::llvmc::value_data * mu::llvmc::generate_function::retrieve_value (mu::llvmc::skeleton::value * value_a)
{
    mu::llvmc::value_data * result;
    auto existing (already_generated.find (value_a));
    if (existing == already_generated.end ())
    {
        auto function (dynamic_cast <mu::llvmc::skeleton::function *> (value_a));
        if (function != nullptr)
        {
            auto existing_function (module.functions.find (function));
            if (existing_function == module.functions.end ())
            {
                result = generate_value (value_a);
            }
            else
            {
                result = new (GC) mu::llvmc::value_data ({0, existing_function->second, nullptr});
            }
        }
        else
        {
            result = generate_value (value_a);
        }
    }
    else
    {
        result = existing->second;
    }
    return result;
}

mu::llvmc::value_data * mu::llvmc::generate_function::generate_value (mu::llvmc::skeleton::value * value_a)
{
    assert (already_generated.find (value_a) == already_generated.end ());
    mu::llvmc::value_data * result;
    auto function (dynamic_cast <mu::llvmc::skeleton::function *> (value_a));
    if (function != nullptr)
    {
        mu::llvmc::generate_function generator (module, function);
        generator.generate ();
        result = new (GC) mu::llvmc::value_data ({0, generator.function_m, nullptr});
        already_generated [value_a] = result;
    }
    else
    {
        auto constant_int (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (value_a));
        if (constant_int != nullptr)
        {
            auto type (generate_type (value_a->type ()));
            result = new (GC) mu::llvmc::value_data ({0, llvm::ConstantInt::get (type, constant_int->value_m), nullptr});
            already_generated [value_a] = result;
        }
        else
        {
            auto element (dynamic_cast <mu::llvmc::skeleton::switch_element *> (value_a));
            if (element != nullptr)
            {/*
                auto branch (entry);
                auto predicate (retrieve_value (element->source->predicate));
                branch = branch->order < predicate.branch->order ? predicate.branch : branch;
                auto & elements (element->source->elements);
                auto branches_l (generate_branch (branch, element->source->predicate, elements));
                {
                    assert (branches_l.size () == elements.size ());
                    auto i (branches_l.begin ());
                    auto j (branches_l.end ());
                    for (auto k (elements.begin ()); i != j; ++i, ++k)
                    {
                        assert (*k != nullptr);
                        assert (*i != nullptr);
                        assert (branches [(*k)->branch] == *i);
                        insert_value (*k, *i, nullptr);
                    }
                }
                assert (already_generated.find (value_a) != already_generated.end ());
                result = already_generated [value_a];
              */
                assert (false); // No switch
            }
            else
            {
                result = generate_single (value_a);
            }
        }
    }
    return result;
}

mu::llvmc::value_data * mu::llvmc::generate_function::generate_single (mu::llvmc::skeleton::value * value_a)
{
    assert (already_generated.find (value_a) == already_generated.end ());
    auto block (body->first);
    llvm::Value * value;
    auto instruction (dynamic_cast <mu::llvmc::skeleton::instruction *> (value_a));
    if (instruction != nullptr)
    {
        for (auto i: instruction->predicates)
        {
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (i) != nullptr);
            auto predicate (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (i)));
            assert (predicate->value->getType ()->isVoidTy ());
            block = block->greatest (predicate->block);
        }
        switch (instruction->type_m)
        {
            case mu::llvmc::instruction_type::add:
            {
                assert (instruction->arguments.size () == 3);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                block = block->greatest (left->block);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2]) != nullptr);
                auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2])));
                block = block->greatest (right->block);
                auto instruction (llvm::BinaryOperator::CreateAdd (left->value, right->value));
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
    {/*
        auto join (dynamic_cast <mu::llvmc::skeleton::join_value *> (value_a));
        if (join != nullptr)
        {
            auto join_branch (find_join_branch (join->arguments));
            if (join_branch == nullptr)
            {
                join_branch = generate_join_branch (join->arguments);;
            }
            assert (already_generated.find (join->arguments [0]) != already_generated.end ());
            auto first_value (already_generated [join->arguments [0]]);
            if (first_value.value != nullptr)
            {
                assert (!join->arguments [0]->type ()->is_bottom_type ());
                auto new_phi (llvm::PHINode::Create (first_value.value->getType (), join->arguments.size ()));
                for (auto i (join->arguments.begin ()), j (join->arguments.end ()); i != j; ++i)
                {
                    auto & value_l (already_generated [*i]);
                    new_phi->addIncoming (value_l.value, value_l.branch->block);
                }
                join_branch->phi_nodes.push_back (new_phi);
                value = new_phi;
            }
            else
            {
                assert (join->arguments [0]->type ()->is_bottom_type ());
                value = nullptr;
            }
        }
        else
        {
            assert (false);
        }*/
        assert (false); // Implement joins
    }
    auto result (new (GC) mu::llvmc::value_data ({block, value, nullptr}));
    already_generated [value_a] = result;
    return result;
}

mu::llvmc::block * mu::llvmc::block::greatest (mu::llvmc::block * other)
{
    
}

mu::llvmc::block * mu::llvmc::block::least (mu::llvmc::block * other)
{
    auto result (greatest (other));
    result = (result == this ? other : this);
    return result;
}

void mu::llvmc::terminator_jump::terminate (llvm::BasicBlock * block_a)
{
}

bool mu::llvmc::terminator::is_exit ()
{
    return false;
}

bool mu::llvmc::terminator_return::is_exit ()
{
    return true;
}

mu::llvmc::terminator_switch::terminator_switch (mu::llvmc::generate_function & generator_a, mu::llvmc::skeleton::value * predicate_a, mu::vector <mu::llvmc::skeleton::switch_element *> const & elements_a) :
generator (generator_a),
predicate (predicate_a),
elements (elements_a)
{
}

void mu::llvmc::terminator_switch::terminate (llvm::BasicBlock * block_a)
{/*
    auto predicate_l (generator.retrieve_value (predicate));
    auto switch_value (llvm::SwitchInst::Create (predicate_l.value, generator.unreachable, elements.size ()));
    block_a->getInstList ().push_back (switch_value);
    for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i)
    {
        auto value_l (generator.retrieve_value ((*i)->value_m));
        auto branch (generator.branches [(*i)->branch]);
        switch_value->addCase (llvm::cast <llvm::ConstantInt> (value_l.value), branch->block);
    }*/
}

mu::llvmc::branch::branch (mu::llvmc::block * first_a, mu::llvmc::block * last_a, mu::llvmc::block * parent_a, llvm::ConstantInt * test_a) :
first (first_a),
last (last_a),
parent (parent_a),
test (test_a)
{
}

llvm::Type * mu::llvmc::generate_function::generate_type (mu::llvmc::skeleton::type * type_a)
{
    assert (!type_a->is_bottom_type ());
    llvm::Type * result;
    auto integer_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type_a));
    if (integer_type != nullptr)
    {
        result = llvm::Type::getIntNTy (module.target->getContext (), integer_type->bits);
    }
    else
    {
        auto pointer_type (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (type_a));
        if (pointer_type != nullptr)
        {
            auto element_type (generate_type (pointer_type->pointed_type));
            assert (element_type != nullptr);
            result = llvm::PointerType::get (element_type, 0);
        }
        else
        {
            assert (false && "Unknown type");
        }
    }
    return result;
}