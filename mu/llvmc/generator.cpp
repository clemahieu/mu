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
function (function_a),
function_return_type (get_return_type (function_a))
{
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
    auto & context (module.target->getContext ());
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
        results.push_back (llvm::Type::getInt8Ty (context));
    }
    llvm::Type * result_type;
    switch (results.size ())
    {
        case 0:
            result_type = llvm::Type::getVoidTy (context);
            break;
        case 1:
            result_type = results [0];
            break;
        default:
        {
            result_type = llvm::StructType::create (context, llvm::ArrayRef <llvm::Type *> (results));
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
            already_generated [*k] = mu::llvmc::value_data ({llvm::ConstantInt::getTrue (context), parameter});
        }
        assert ((i != j) == (k != l));
    }
    function_m = function_l;
    module.target->getFunctionList ().push_back (function_l);
    assert (module.functions.find (function) == module.functions.end ());
    module.functions [function] = function_l;
    auto entry (llvm::BasicBlock::Create (context));
    last = entry;
    function_l->getBasicBlockList().push_back (entry);
    switch (function_return_type)
    {
        case mu::llvmc::function_return_type::b0:
            last->getInstList ().push_back (new llvm::UnreachableInst (function_l->getContext ()));
            break;
        case mu::llvmc::function_return_type::b1v0:
            for (auto i: function->results)
            {
                auto result (retrieve_value (i->value));
                assert (i->type->is_bottom_type ());
            }
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext ()));
            break;
        case mu::llvmc::function_return_type::b1v1:
        {
            llvm::Value * the_value (nullptr);
            for (auto i: function->results)
            {
                auto result (retrieve_value (i->value));
                assert (the_value == nullptr || i->type->is_bottom_type ());
                the_value = i->type->is_bottom_type () ? the_value : result.value;
            }
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext (), the_value));
        }
            break;
        case mu::llvmc::function_return_type::b1vm:
        {
            assert (function->branch_offsets.size () == 1);
            assert (function->branch_offsets [0] == 0);
            llvm::Value * result (llvm::UndefValue::get (function_type->getReturnType ()));
            unsigned index (0);
            for (auto i: function->results)
            {
                auto result_value (retrieve_value (i->value));
                if (!i->type->is_bottom_type ())
                {
                    auto insert = llvm::InsertValueInst::Create (result, result_value.value, llvm::ArrayRef <unsigned> (index));
                    last->getInstList ().push_back (insert);
                    result = insert;
                    ++index;
                }
            }
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext (), result));
        }
            break;
        case mu::llvmc::function_return_type::bmv0:
        {
            auto results (generate_result_set ());
            assert (results.size () == 1);
            last->getInstList ().push_back (llvm::ReturnInst::Create (function_l->getContext (), results [0]));
        }
            break;
        case mu::llvmc::function_return_type::bmvm:
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
        }
            break;
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
    auto first_branch (function->branch_offsets.begin ());
    auto last_branch (function->branch_offsets.end ());
    size_t j (0);
    uint8_t selector_number (0);
    size_t k (first_branch == last_branch ? ~0 : *(++first_branch));
    for (auto i: function->results)
    {
        auto result_l (retrieve_value (i->value));
        if (!i->type->is_bottom_type())
        {
            result.push_back (result_l.value);
        }
        auto instruction (llvm::BinaryOperator::CreateAnd (predicate, result_l.predicate));
        last->getInstList ().push_back (instruction);
        predicate = instruction;
        ++j;
        if (j == k)
        {
            auto selector_new (llvm::SelectInst::Create (predicate, llvm::ConstantInt::get (type, selector_number), selector));
            last->getInstList().push_back (selector_new);
            selector = selector_new;
            predicate = llvm::ConstantInt::getTrue (context);
            ++selector_number;
            k = first_branch == last_branch ? ~0 : *(++first_branch);
        }
    }
    auto selector_new (llvm::SelectInst::Create (predicate, llvm::ConstantInt::get (type, selector_number), selector));
    last->getInstList().push_back (selector_new);
    selector = selector_new;
    result.push_back (selector);
    return result;
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
                result = mu::llvmc::value_data ({llvm::ConstantInt::getTrue (module.target->getContext ()), existing_function->second});
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
        result = mu::llvmc::value_data ({llvm::ConstantInt::getTrue (module.target->getContext ()), generator.function_m});
        already_generated [value_a] = result;
    }
    else
    {
        auto constant_int (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (value_a));
        if (constant_int != nullptr)
        {
            auto type (generate_type (value_a->type ()));
            result = mu::llvmc::value_data ({llvm::ConstantInt::getTrue (module.target->getContext ()), llvm::ConstantInt::get (type, constant_int->value_m)});
            already_generated [value_a] = result;
        }
        else
        {
            auto element (dynamic_cast <mu::llvmc::skeleton::switch_element *> (value_a));
            if (element != nullptr)
            {
                auto predicate (process_predicates (element->source->predicates));
                auto predicate_l (retrieve_value (element->source->predicate));
                auto instruction (llvm::BinaryOperator::CreateAnd (predicate, predicate_l.predicate));
                last->getInstList ().push_back (instruction);
                predicate = instruction;
                auto & elements (element->source->elements);
                for (auto i: elements)
                {
                    auto compare (new llvm::ICmpInst (llvm::CmpInst::Predicate::ICMP_EQ, predicate_l.value, llvm::ConstantInt::get (predicate_l.value->getType (), i->value_m->value_m)));
                    last->getInstList().push_back (compare);
                    auto switch_predicate (llvm::BinaryOperator::CreateAnd (predicate, compare));
                    last->getInstList().push_back (switch_predicate);
                    already_generated [i] = mu::llvmc::value_data ({switch_predicate, nullptr});
                }
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

llvm::Value * mu::llvmc::generate_function::process_predicates (mu::vector <mu::llvmc::skeleton::node *> const & predicates_a)
{
    auto last_l (last);
    llvm::Value * predicate (llvm::ConstantInt::getTrue (last->getContext ()));
    for (auto i: predicates_a)
    {
        assert (dynamic_cast <mu::llvmc::skeleton::value *> (i) != nullptr);
        auto value_l (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (i)));
        auto instruction (llvm::BinaryOperator::CreateAnd (predicate, value_l.predicate));
        last_l->getInstList ().push_back (instruction);
    }
    return predicate;
}

mu::llvmc::value_data mu::llvmc::generate_function::generate_single (mu::llvmc::skeleton::value * value_a)
{
    assert (already_generated.find (value_a) == already_generated.end ());
    auto & context (module.target->getContext ());
    auto instruction (dynamic_cast <mu::llvmc::skeleton::instruction *> (value_a));
    llvm::Value * predicate;
    llvm::Instruction * value;
    if (instruction != nullptr)
    {
        auto predicate_l (process_predicates (instruction->predicates));
        switch (instruction->type_m)
        {
            case mu::llvmc::instruction_type::add:
            {
                assert (instruction->arguments.size () == 3);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1]) != nullptr);
                auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                auto p_left (llvm::BinaryOperator::CreateAnd (predicate_l, left.predicate));
                last->getInstList ().push_back (p_left);
                assert (dynamic_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2]) != nullptr);
                auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [2])));
                auto p_right (llvm::BinaryOperator::CreateAnd (p_left, right.predicate));
                last->getInstList ().push_back (p_right);
                predicate = p_right;
                value = llvm::BinaryOperator::CreateAdd (left.value, right.value);
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
        {/*
            mu::llvmc::block * least_specific_block (nullptr);
            assert (join->arguments.size () > 1);
            for (auto i: join->arguments)
            {
                auto value (retrieve_value (i));
                least_specific_block = value->block->least (least_specific_block);
            }
            llvm::Value * value (llvm::Undef)
            for (auto i: join->arguments)
            {
                pull_value (least_specific_block->branch, i);
            }
            assert (least_specific_block != nullptr);
            
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
            }*/
            assert (false); // Implement joins
        }
        else
        {
            assert (false);
        }
    }
    auto execution_block (llvm::BasicBlock::Create (context));
    auto new_last (llvm::BasicBlock::Create (context));
    last->getInstList ().push_back (llvm::BranchInst::Create (execution_block, new_last, predicate));
    function_m->getBasicBlockList().push_back (execution_block);
    function_m->getBasicBlockList().push_back (new_last);
    auto real_value (llvm::PHINode::Create (value->getType (), 2));
    execution_block->getInstList().push_back (value);
    execution_block->getInstList().push_back (llvm::BranchInst::Create (new_last));
    real_value->addIncoming (llvm::UndefValue::get (value->getType ()), last);
    real_value->addIncoming (value, execution_block);
    new_last->getInstList().push_back (real_value);
    last = new_last;
    auto result (mu::llvmc::value_data ({predicate, real_value}));
    already_generated [value_a] = result;
    return result;
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