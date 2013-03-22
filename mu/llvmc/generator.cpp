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
function (function_a)
{
    branches [function->entry] = entry;
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
    for (auto i (function->results.begin ()), j (function->results.end ()); i != j; ++i)
    {
        for (auto k ((*i).begin ()), l ((*i).end ()); k != l; ++k)
        {
            auto type_s ((*k)->type);
            if (!type_s->is_bottom_type())
            {
                auto type_l (generate_type (type_s));
                results.push_back (type_l);
            }
        }
    }
    if (function->results.size () > 1)
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
            entry->available_variables.insert (entry->available_variables.end (), true);
            llvm::Value * parameter (i);
            already_generated [*k] = mu::llvmc::value_data ({entry->available_variables.size () - 1, parameter, entry});
        }
        assert ((i != j) == (k != l));
    }
    function_m = function_l;
    function_l->getBasicBlockList ().push_back (entry->block);
    module.target->getFunctionList ().push_back (function_l);
    assert (module.functions.find (function) == module.functions.end ());
    module.functions [function] = function_l;
    if (function->results.empty ())
    {
        function_l->addFnAttr (llvm::Attributes::NoReturn);
    }
    for (auto i (function->results.begin ()), j (function->results.end ()); i != j; ++i)
    {
        for (auto k ((*i).begin ()), l ((*i).end ()); k != l; ++k)
        {
            auto value_l (retrieve_value ((*k)->value));
            // Populate already_generated
        }
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
index (~0),
generator (generator_a)
{
}

void mu::llvmc::terminator_return::set_index (size_t index_a)
{
    auto index_l (index);
    assert (index_l == ~0 || index_l == index_a);
    index = index_a;
}

void mu::llvmc::terminator_return::terminate (llvm::BasicBlock * block_a)
{
    switch (generator.function->results.size ())
    {
        case 0:
        {
            block_a->getInstList ().push_back (new llvm::UnreachableInst (block_a->getContext()));
        }
            break;
        case 1:
        {
            auto & results (generator.function->results [0]);
            switch (results.size ())
            {
                case 0:
                {
                    block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext ()));
                }
                    break;
                case 1:
                {
                    assert (generator.already_generated.find (results [0]->value) != generator.already_generated.end ());
                    block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext(), generator.already_generated [results [0]->value].value));
                }
                    break;
                default:
                {
                    std::vector <llvm::Value *> result_values;
                    for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
                    {
                        assert (generator.already_generated.find ((*i)->value) != generator.already_generated.end ());
                        auto generated (generator.already_generated [(*i)->value].value);
                        result_values.push_back (generated);
                    }
                    auto result_type (generator.function_m->getReturnType ());
                    llvm::Value * result_value (llvm::UndefValue::get (result_type));
                    {
                        unsigned k (0);
                        for (auto i (result_values.begin ()), j (result_values.end ()); i != j; ++i, ++k)
                        {
                            auto inst (llvm::InsertValueInst::Create (result_value, *i, llvm::ArrayRef <unsigned> (k)));
                            block_a->getInstList ().push_back (inst);
                            result_value = inst;
                        }
                    }
                    block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext (), result_value));
                }
                    break;
            }
        }
            break;
        default:
        {
            assert (index != ~0);
            assert (generator.function->results.size () > index);
            auto index_l (index);
            auto & results (generator.function->results [index_l]);
            size_t k (0);
            for (auto j (0); j < index_l; ++j)
            {
                k += generator.function->results [j].size ();
            }
            std::vector <llvm::Value *> result_values;
            for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
            {
                assert (generator.already_generated.find ((*i)->value) != generator.already_generated.end ());
                auto generated (generator.already_generated [(*i)->value].value);
                result_values.push_back (generated);
            }
            auto result_type (generator.function_m->getReturnType ());
            llvm::Value * result_value (llvm::UndefValue::get (result_type));
            {
                for (auto i (result_values.begin ()), j (result_values.end ()); i != j; ++i, ++k)
                {
                    auto inst (llvm::InsertValueInst::Create (result_value, *i, llvm::ArrayRef <unsigned> (k)));
                    block_a->getInstList ().push_back (inst);
                    result_value = inst;
                }
            }
            auto selector (llvm::ConstantInt::get (llvm::Type::getInt8Ty (generator.function_m->getContext ()), index_l));
            auto inst (llvm::InsertValueInst::Create (result_value, selector, llvm::ArrayRef <unsigned> (llvm::cast <llvm::StructType> (result_type)->getNumElements () - 1)));
            block_a->getInstList ().push_back (inst);
            result_value = inst;
            block_a->getInstList ().push_back (llvm::ReturnInst::Create (block_a->getContext (), result_value));
        }
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

mu::llvmc::branch::branch (llvm::BasicBlock * block_a, size_t order_a, mu::llvmc::branch * next_branch_a, mu::llvmc::terminator * terminator_a, std::vector <bool> const & available_variables_a) :
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
    mu::llvmc::value_data result;
    auto function (dynamic_cast <mu::llvmc::skeleton::function *> (value_a));
    if (function != nullptr)
    {
        mu::llvmc::generate_function generator (module, function);
        generator.generate ();
        result = mu::llvmc::value_data ({0, generator.function_m, nullptr});
    }
    else
    {
        auto constant_int (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (value_a));
        if (constant_int != nullptr)
        {
            auto type (generate_type (value_a->type ()));
            result = mu::llvmc::value_data ({0, llvm::ConstantInt::get (type, constant_int->value_m), nullptr});
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
    llvm::Value * value;
    auto branch (branches [function->entry]);
    auto instruction (dynamic_cast <mu::llvmc::skeleton::instruction *> (value_a));
    if (instruction != nullptr)
    {
        for (auto i (instruction->predicates.begin ()), j (instruction->predicates.end ()); i != j; ++i)
        {
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (*i) != nullptr);
            auto predicate (generate_local_value (static_cast <mu::llvmc::skeleton::value *> (*i)));
            branch = branch->order < predicate.branch->order ? predicate.branch : branch;
        }
        switch (instruction->type_m)
        {
            case mu::llvmc::instruction_type::add:
            {
                assert (instruction->arguments.size () == 2);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [0]) != nullptr);
                auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [0])));
                branch = branch->order < left.branch->order ? left.branch : branch;
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                branch = branch->order < right.branch->order ? right.branch : branch;
                auto instruction (llvm::BinaryOperator::CreateAdd (left.value, right.value));
                value = instruction;
                branch->instructions.push_back (instruction);
                break;
            }
            case mu::llvmc::instruction_type::switch_i:
            {
                assert (instruction->arguments.size () > 1);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [0]) != nullptr);
                auto predicate (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [0])));
                branch = branch->order < predicate.branch->order ? predicate.branch : branch;
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                auto default_l (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                if (default_l.branch != nullptr)
                {
                    branch = branch->order < default_l.branch->order ? default_l.branch : branch;
                }
                auto switch_value (llvm::SwitchInst::Create (default_l.value, branch->block, instruction->arguments.size () - 2));
                value = switch_value;
                for (auto i (instruction->arguments.begin () + 2), j (instruction->arguments.end ()); i != j; ++i)
                {
                    assert (dynamic_cast <mu::llvmc::skeleton::value *> (*i) != nullptr);
                    auto value_l (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (*i)));
                    assert (value_l.branch == nullptr);
                    switch_value->addCase (llvm::cast <llvm::ConstantInt> (value_l.value), branch->block);
                }
                auto first_bit (entry->available_variables.size ());
                auto branches (generate_branch (branch, instruction->arguments));
                auto & switch_data (switches [value_a]);
                {
                    auto i (instruction->arguments.begin () + 2);
                    for (auto k (branches.begin ()), l (branches.end ()); k != l; ++k, ++i, ++first_bit)
                    {
                        auto value_l (static_cast <mu::llvmc::skeleton::value *> (*i));
                        switch_data [value_l] = mu::llvmc::value_data ({first_bit, value, *k});
                    }
                }
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
        auto element (dynamic_cast <mu::llvmc::skeleton::switch_element *> (value_a));
        if (element != nullptr)
        {
            auto switch_instruction (generate_local_value (element->call));
            assert (switches.find (element->call) != switches.end ());
            auto & branches (switches [element->call]);
            assert (branches.find (value_a) != branches.end ());
            auto value_l (branches [value_a]);
            value = switch_instruction.value;
            already_generated [value_a] = value_l;
        }
        else
        {
            assert (false);
        }
    }
    auto result (insert_value (value_a, branch, value));
    return result;
}

mu::vector <mu::llvmc::branch *> mu::llvmc::generate_function::generate_branch (mu::llvmc::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a)
{
    auto count (arguments_a.size () - 2);
    mu::vector <mu::llvmc::branch *> result;
    for (auto i (branch_a->next_branch); i != nullptr; i = i->next_branch)
    {
        i->order += count;
    }
    for (auto i (branch_a->terminator->successors.begin ()), j (branch_a->terminator->successors.end ()); i != j; ++i)
    {
        auto erased ((*i)->predecessors.erase (branch_a));
        assert (erased == 1);
    }
    for (size_t i (0), j (count); i != j; ++i)
    {
        auto block (llvm::BasicBlock::Create (function_m->getContext ()));
        auto new_branch (new (GC) mu::llvmc::branch (block, branch_a->order + (j - i), branch_a->next_branch, branch_a->terminator, branch_a->available_variables));
        for (auto i (new_branch->terminator->successors.begin ()), j (new_branch->terminator->successors.end ()); i != j; ++i)
        {
            (*i)->predecessors.insert (new_branch);
        }
        branch_a->next_branch = new_branch;
        new_branch->predecessors.insert (branch_a);
        result.push_back (new_branch);
    }
    auto new_terminator (new (GC) mu::llvmc::terminator_switch (*this, arguments_a));
    branch_a->terminator = new_terminator;
    return result;
}

mu::llvmc::terminator_switch::terminator_switch (mu::llvmc::generate_function & generator_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a) :
generator (generator_a),
arguments (arguments_a)
{
}

void mu::llvmc::terminator_switch::terminate (llvm::BasicBlock * block_a)
{
    
}

mu::llvmc::value_data mu::llvmc::generate_function::insert_value (mu::llvmc::skeleton::value * value_a, mu::llvmc::branch * branch_a, llvm::Value * val_a)
{
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