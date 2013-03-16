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
function (function_a)
{    
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
            auto type_l (generate_type ((*k)->type));
            results.push_back (type_l);
        }
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
            results.push_back (llvm::Type::getInt8Ty (module.target->getContext ()));
            result_type = llvm::StructType::create (module.target->getContext(), llvm::ArrayRef <llvm::Type *> (results));
        }
    }
    auto function_type (llvm::FunctionType::get (result_type, llvm::ArrayRef <llvm::Type *> (parameters), false));
    auto function_l (llvm::Function::Create (function_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage));
    auto entry (new (GC) mu::llvmc::branch (0, nullptr, nullptr));
    branches [function->entry] = entry;
    {
        auto i (function_l->arg_begin());
        auto j (function_l->arg_end());
        auto k (function->parameters.begin ());
        auto l (function->parameters.end ());
        while (i != j)
        {
            assert (k != l);
            entry->available_variables.insert (entry->available_variables.end (), true);
            llvm::Value * parameter (i);
            already_generated [*k] = mu::llvmc::value_data ({entry->available_variables.size () - 1, parameter, entry});
        }
        assert ((i != j) == (k != l));
    }
    function_m = function_l;
    module.target->getFunctionList ().push_back (function_l);
    assert (module.functions.find (function) == module.functions.end ());
    module.functions [function] = function_l;
    if (!function->results.empty ())
    {
        function_l->addFnAttr (llvm::Attributes::NoReturn);
    }
    for (auto i (function->results.begin ()), j (function->results.end ()); i != j; ++i)
    {
        std::vector <llvm::Value *> result_set;
        for (auto k ((*i).begin ()), l ((*i).end ()); k != l; ++k)
        {
            auto value_l (retrieve_value ((*k)->value));
            result_set.push_back (value_l);
        }
    }
}

mu::llvmc::branch::branch (size_t order_a, mu::llvmc::branch * next_branch_a, mu::llvmc::terminator * terminator_a) :
order (order_a),
next_branch (next_branch_a),
terminator (terminator_a)
{
}

llvm::Value * mu::llvmc::generate_function::retrieve_value (mu::llvmc::skeleton::value * value_a)
{
    llvm::Value * result;
    auto existing (already_generated.find (value_a));
    if (existing == already_generated.end ())
    {
        auto function (dynamic_cast <mu::llvmc::skeleton::function *> (value_a));
        if (function != nullptr)
        {
            auto existing_function (module.functions.find (function));
            if (existing_function == module.functions.end ())
            {
                result = create (value_a);
            }
            else
            {
                result = existing_function->second;
            }
        }
        else
        {
            result = create (value_a);
        }
    }
    else
    {
        result = existing->second.value;
    }
    return result;
}

llvm::Value * mu::llvmc::generate_function::create (mu::llvmc::skeleton::value * value_a)
{
    llvm::Value * result;
    auto function (dynamic_cast <mu::llvmc::skeleton::function *> (value_a));
    if (function != nullptr)
    {
        mu::llvmc::generate_function generator (module, function);
        generator.generate ();
        result = generator.function_m;
    }
    else
    {
        auto instruction (dynamic_cast <mu::llvmc::skeleton::instruction *> (value_a));
        if (instruction != nullptr)
        {
            switch (instruction->type_m)
            {
                case mu::llvmc::instruction_type::add:
                {
                    auto left (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [0])));
                    auto right (retrieve_value (static_cast <mu::llvmc::skeleton::value *> (instruction->arguments [1])));
                    result = nullptr;
                }
                    break;
                default:
                    assert (false);
                    break;
            }
        }
        else
        {
            assert (false);
        }
    }
    return result;
}

llvm::Type * mu::llvmc::generate_function::generate_type (mu::llvmc::skeleton::type * type_a)
{
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
            result = llvm::PointerType::get (element_type, 0);
        }
        else
        {
            assert (false && "Unknown type");
        }
    }
    return result;
}