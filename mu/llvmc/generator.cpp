#include <mu/llvmc/generator.hpp>

#include <mu/llvmc/ast.hpp>
#include <mu/core/error_string.hpp>
#include <mu/llvmc/wrapper.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>

#include <gc_cpp.h>

mu::llvmc::generator::generator ():
result ({nullptr, nullptr}),
module (nullptr),
function (nullptr)
{
}

void mu::llvmc::generator::generate (mu::llvmc::ast::node * node_a)
{
    auto module_l (dynamic_cast <mu::llvmc::ast::module *> (node_a));
    if (module_l != nullptr)
    {
        module = new llvm::Module ("test", context);
        for (auto i (module_l->functions.begin ()), j (module_l->functions.end ()); i != j; ++i)
        {
            auto function (dynamic_cast <mu::llvmc::ast::function *> (*i));
            if (function != nullptr)
            {
                generate_function (function);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Module is expected to contain functions");
            }
        }
        if (result.error == nullptr)
        {
            result.module = module;
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a module");
    }
}

void mu::llvmc::generator::generate_function (mu::llvmc::ast::function * function_a)
{
    std::vector <llvm::Type *> parameter_types;
    for (auto i (function_a->parameters.begin ()), j (function_a->parameters.end ()); i != j && result.error == nullptr; ++i)
    {
        auto type (dynamic_cast <mu::llvmc::wrapper::type *> ((*i)->type));
        if (type != nullptr)
        {
            parameter_types.push_back (type->type_m);
        }
        else
        {
            result.error = new (GC) mu::core::error_string (U"Expecting type");
        }
    }
    std::vector <llvm::Type *> return_types;
    if (function_a->results.size () > 1)
    {
        return_types.push_back (llvm::Type::getInt8Ty (context));
    }
    for (auto i (function_a->results.begin ()), j (function_a->results.end ()); i != j && result.error == nullptr; ++i)
    {
        for (auto k (i->begin ()), l (i->end ()); k != l; ++k)
        {
            auto type (dynamic_cast <mu::llvmc::wrapper::type *> ((*k)->written_type));
            if (type != nullptr)
            {
                return_types.push_back (type->type_m);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Expecting type");
            }
        }
    }
    auto function_type (llvm::FunctionType::get (llvm::StructType::get (context, return_types), parameter_types, false));
    function = llvm::Function::Create (function_type, llvm::GlobalValue::LinkageTypes::InternalLinkage, "", module);
}
