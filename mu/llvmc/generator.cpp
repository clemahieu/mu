#include <mu/llvmc/generator.hpp>

#include <mu/llvmc/ast.hpp>
#include <mu/core/error_string.hpp>

#include <llvm/Module.h>

#include <gc_cpp.h>

mu::llvmc::module_result mu::llvmc::generator::generate (mu::llvmc::ast::node * node_a)
{
    mu::llvmc::module_result result ({nullptr, nullptr});
    auto module (dynamic_cast <mu::llvmc::ast::module *> (node_a));
    if (module != nullptr)
    {
        auto module_result (new llvm::Module ("", context));
        
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a module");
    }
    return result;
}