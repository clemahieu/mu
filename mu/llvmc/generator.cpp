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
entry (new (GC) mu::llvmc::branch (llvm::BasicBlock::Create (module.target->getContext ()), 0, nullptr, new (GC) mu::llvmc::terminator_return (*this))),
unreachable (llvm::BasicBlock::Create (module.target->getContext ())),
terminating_branch (0),
function (function_a),
function_return_type (get_return_type (function_a))
{
    unreachable->getInstList ().push_back (new llvm::UnreachableInst (module.target->getContext ()));
    branches [function->entry] = entry;
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
        branch_offsets.push_back (results.size ());
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
            entry->available_variables.push_back (true);
            llvm::Value * parameter (i);
            already_generated [*k] = mu::llvmc::value_data ({entry->available_variables.size () - 1, parameter, entry});
        }
        assert ((i != j) == (k != l));
    }
    function_m = function_l;
    function_l->getBasicBlockList ().push_back (entry->block);
    function_l->getBasicBlockList ().push_back (unreachable);
    module.target->getFunctionList ().push_back (function_l);
    assert (module.functions.find (function) == module.functions.end ());
    module.functions [function] = function_l;
    if (function->results.empty ())
    {
        function_l->addFnAttr (llvm::Attributes::NoReturn);
    }
    for (auto i (function->results.begin ()), j (function->results.end ()); i != j; ++i)
    {
        auto value_l (retrieve_value ((*i)->value));
        // Populate already_generated
    }
    for (auto i (entry); i != nullptr; i = i->next_branch)
    {
        auto block (i->block);
        for (auto k (i->phi_nodes.begin ()), l (i->phi_nodes.end ()); k != l; ++k)
        {
            block->getInstList ().push_back (*k);
        }
        for (auto k (i->instructions.begin ()), l (i->instructions.end ()); k != l; ++k)
        {
            block->getInstList ().push_back (*k);
        }
        i->terminator->terminate (i->block);
    }
}

mu::llvmc::terminator_return::terminator_return (mu::llvmc::generate_function & generator_a) :
generator (generator_a)
{
}

void mu::llvmc::terminator_return::terminate (llvm::BasicBlock * block_a)
{
    auto index_l (generator.terminating_branch);
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
    }
}

mu::llvmc::branch::branch (llvm::BasicBlock * block_a, size_t order_a, mu::llvmc::branch * next_branch_a, mu::llvmc::terminator * terminator_a) :
block (block_a),
order (order_a),
next_branch (next_branch_a),
terminator (terminator_a)
{
}

mu::llvmc::branch::branch (llvm::BasicBlock * block_a, size_t order_a, mu::llvmc::branch * next_branch_a, mu::llvmc::terminator * terminator_a, boost::dynamic_bitset <> const & available_variables_a) :
block (block_a),
order (order_a),
next_branch (next_branch_a),
terminator (terminator_a),
available_variables (available_variables_a)
{
}


mu::llvmc::value_data mu::llvmc::generate_function::retrieve_value (mu::llvmc::skeleton::value * value_a)
{
    mu::llvmc::value_data result;
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
                result = mu::llvmc::value_data ({0, existing_function->second, nullptr});;
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

mu::llvmc::value_data mu::llvmc::generate_function::generate_value (mu::llvmc::skeleton::value * value_a)
{
    assert (already_generated.find (value_a) == already_generated.end ());
    mu::llvmc::value_data result;
    auto function (dynamic_cast <mu::llvmc::skeleton::function *> (value_a));
    if (function != nullptr)
    {
        mu::llvmc::generate_function generator (module, function);
        generator.generate ();
        result = mu::llvmc::value_data ({0, generator.function_m, nullptr});
        already_generated [value_a] = result;
    }
    else
    {
        auto constant_int (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (value_a));
        if (constant_int != nullptr)
        {
            auto type (generate_type (value_a->type ()));
            result = mu::llvmc::value_data ({0, llvm::ConstantInt::get (type, constant_int->value_m), nullptr});
            already_generated [value_a] = result;
        }
        else
        {
            result = generate_local_value (value_a);
        }
    }
    return result;
}

mu::llvmc::value_data mu::llvmc::generate_function::generate_local_value (mu::llvmc::skeleton::value * value_a)
{
    assert (already_generated.find (value_a) == already_generated.end ());
    mu::llvmc::value_data result;
    auto element (dynamic_cast <mu::llvmc::skeleton::switch_element *> (value_a));
    if (element != nullptr)
    {
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
    }
    else
    {
        result = generate_single (value_a);
    }
    return result;
}

mu::llvmc::value_data mu::llvmc::generate_function::generate_single (mu::llvmc::skeleton::value * value_a)
{
    assert (already_generated.find (value_a) == already_generated.end ());
    llvm::Value * value;
    auto branch (branches [function->entry]);
    auto instruction (dynamic_cast <mu::llvmc::skeleton::instruction *> (value_a));
    if (instruction != nullptr)
    {
        for (auto i (instruction->predicates.begin ()), j (instruction->predicates.end ()); i != j; ++i)
        {
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (*i) != nullptr);
            auto predicate (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (*i)));
            branch = branch->order < predicate.branch->order ? predicate.branch : branch;
        }
        switch (instruction->type_m)
        {
            case mu::llvmc::instruction_type::add:
            {
                assert (instruction->arguments.size () == 3);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                branch = branch->order < left.branch->order ? left.branch : branch;
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2]) != nullptr);
                auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2])));
                branch = branch->order < right.branch->order ? right.branch : branch;
                auto instruction (llvm::BinaryOperator::CreateAdd (left.value, right.value));
                value = instruction;
                branch->instructions.push_back (instruction);
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
            auto join_branch (find_join_branch (join->arguments));
            if (join_branch == nullptr)
            {
                auto minimum_branch (branches [join->arguments [0]->branch]);
                for (auto i (join->arguments.begin () + 1), j (join->arguments.end ()); i != j; ++i)
                {
                    auto branch_l (branches [(*i)->branch]);
                    minimum_branch = branch_l->order < minimum_branch->order ? branch_l : minimum_branch;
                }
                join_branch = generate_join_branch (minimum_branch, join->arguments);;
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
        }
    }
    auto result (insert_value (value_a, branch, value));
    return result;
}

mu::llvmc::branch::branch (llvm::BasicBlock * block_a, mu::llvmc::terminator * terminator_a, boost::dynamic_bitset <> const & available_variables_a) :
block (block_a),
terminator (terminator_a),
available_variables (available_variables_a)
{
}

void mu::llvmc::terminator_jump::terminate (llvm::BasicBlock * block_a)
{
    block_a->getInstList ().push_back (llvm::BranchInst::Create (branch->block));
}

mu::llvmc::branch * mu::llvmc::generate_function::generate_join_branch (mu::llvmc::branch * predecessor, mu::vector <mu::llvmc::skeleton::value *> const & arguments_a)
{
    auto new_terminator (new (GC) mu::llvmc::terminator_jump);
    assert (branches.find (function->entry) != branches.end ());
    auto minimum (branches [function->entry]);
    auto block (llvm::BasicBlock::Create (function_m->getContext ()));
    auto new_branch (new (GC) mu::llvmc::branch (block, predecessor->terminator, minimum->available_variables));
    function_m->getBasicBlockList ().push_back (block);
    for (auto i (arguments_a.begin ()), j (arguments_a.end ()); i != j; ++i)
    {
        assert (branches.find ((*i)->branch) != branches.end ());
        auto branch_l (branches [(*i)->branch]);
        set_exit_terminator_to_new (branch_l, new_terminator, new_branch);
        minimum = branch_l->order < minimum->order ? branch_l : minimum;
    }
    for (auto i (minimum->next_branch); i != nullptr; i = i->next_branch)
    {
        auto i_l (i->order);
        i->order = i_l + 1;
    }
    new_branch->order = minimum->order + 1;
    new_branch->next_branch = minimum->next_branch;
    minimum->next_branch = new_branch;
    new_terminator->branch = new_branch;
    return new_branch;
}

bool mu::llvmc::terminator::is_exit ()
{
    return false;
}

bool mu::llvmc::terminator_return::is_exit ()
{
    return true;
}

mu::llvmc::branch * mu::llvmc::generate_function::set_exit_terminator_to_new (mu::llvmc::branch * branch, mu::llvmc::terminator * terminator_a, mu::llvmc::branch * target)
{
    auto result (branch);
    if (branch->terminator->is_exit ())
    {
        branch->terminator = terminator_a;
        target->predecessors.insert (branch);
        target->available_variables |= branch->available_variables;
        result = branch;
    }
    else
    {
        for (auto i (branch->terminator->successors.begin ()), j (branch->terminator->successors.end ()); i != j; ++i)
        {
            auto result_l (set_exit_terminator_to_new (branch, terminator_a, target));
            result = result_l->order < result->order ? result_l : result;
        }
    }
    return result;
}

mu::llvmc::branch * mu::llvmc::generate_function::find_join_branch (mu::vector <mu::llvmc::skeleton::value *> const & arguments_a)
{
    auto first_value (retrieve_value (arguments_a [0]));
    auto current_branch (first_value.branch);
    for (auto i (arguments_a.begin () + 1), j (arguments_a.end ()); i != j && current_branch != nullptr; ++i)
    {
        auto value (retrieve_value (*i));
        current_branch = find_meeting_branch (current_branch, branches [(*i)->branch], value.bit_index);
    }
    return current_branch;
}

mu::llvmc::branch * mu::llvmc::generate_function::find_meeting_branch (mu::llvmc::branch * current_branch, mu::llvmc::branch * other_a, size_t bit_index)
{
    mu::llvmc::branch * result (nullptr);
    for (auto i (current_branch->successors.begin ()), j (current_branch->successors.end ()); i != j && result == nullptr; ++i)
    {
        if ((*i)->available_variables [bit_index])
        {
            result = *i;
        }
        else
        {
            result = find_meeting_branch (current_branch, *i, bit_index);
        }
    }
    return result;
}

mu::vector <mu::llvmc::branch *> mu::llvmc::generate_function::generate_branch (mu::llvmc::branch * branch_a, mu::llvmc::skeleton::value * predicate_a, mu::vector <mu::llvmc::skeleton::switch_element *> const & elements_a)
{
    mu::vector <mu::llvmc::branch *> result;
    for (auto i (branch_a->next_branch); i != nullptr; i = i->next_branch)
    {
        i->order += elements_a.size ();
    }
    for (auto i (branch_a->terminator->successors.begin ()), j (branch_a->terminator->successors.end ()); i != j; ++i)
    {
        auto erased ((*i)->predecessors.erase (branch_a));
        assert (erased == 1);
    }
    for (size_t i (0), j (elements_a.size ()); i != j; ++i)
    {
        auto block (llvm::BasicBlock::Create (function_m->getContext ()));
        function_m->getBasicBlockList ().push_back (block);
        auto new_branch (new (GC) mu::llvmc::branch (block, branch_a->order + (j - i), branch_a->next_branch, branch_a->terminator, branch_a->available_variables));
        branches [elements_a [i]->branch] = new_branch;
        for (auto i (new_branch->terminator->successors.begin ()), j (new_branch->terminator->successors.end ()); i != j; ++i)
        {
            (*i)->predecessors.insert (new_branch);
        }
        branch_a->next_branch = new_branch;
        new_branch->predecessors.insert (branch_a);
        result.push_back (new_branch);
    }
    auto new_terminator (new (GC) mu::llvmc::terminator_switch (*this, predicate_a, elements_a));
    branch_a->terminator = new_terminator;
    return result;
}

mu::llvmc::terminator_switch::terminator_switch (mu::llvmc::generate_function & generator_a, mu::llvmc::skeleton::value * predicate_a, mu::vector <mu::llvmc::skeleton::switch_element *> const & elements_a) :
generator (generator_a),
predicate (predicate_a),
elements (elements_a)
{
}

void mu::llvmc::terminator_switch::terminate (llvm::BasicBlock * block_a)
{
    auto predicate_l (generator.retrieve_value (predicate));
    auto switch_value (llvm::SwitchInst::Create (predicate_l.value, generator.unreachable, elements.size ()));
    block_a->getInstList ().push_back (switch_value);
    for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i)
    {
        auto value_l (generator.retrieve_value ((*i)->value_m));
        auto branch (generator.branches [(*i)->branch]);
        switch_value->addCase (llvm::cast <llvm::ConstantInt> (value_l.value), branch->block);
    }
}

mu::llvmc::value_data mu::llvmc::generate_function::insert_value (mu::llvmc::skeleton::value * value_a, mu::llvmc::branch * branch_a, llvm::Value * val_a)
{
    assert (value_a != nullptr);
    assert (branch_a != nullptr);
    assert (already_generated.find (value_a) == already_generated.end ());
    auto new_bit (entry->available_variables.size ());
    for (auto i (entry); i != nullptr; i = i->next_branch)
    {
        i->available_variables.push_back (false);
    }
    set_bit_and_successors (new_bit, branch_a);
    mu::llvmc::value_data result ({new_bit, val_a, branch_a});
    already_generated [value_a] = result;
    return result;
}

void mu::llvmc::generate_function::set_bit_and_successors (size_t bit_a, mu::llvmc::branch * branch_a)
{
    branch_a->available_variables [bit_a] = true;
    for (auto i (branch_a->successors.begin ()), j (branch_a->successors.end ()); i != j; ++i)
    {
        set_bit_and_successors (bit_a, branch_a);
    }
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