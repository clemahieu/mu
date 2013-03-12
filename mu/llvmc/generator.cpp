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

mu::llvmc::module_result mu::llvmc::generator::generate (llvm::LLVMContext &context_a, mu::llvmc::skeleton::module *module_a)
{
    mu::llvmc::module_result result {nullptr, nullptr};
    auto module (new llvm::Module ("", context_a));
    for (auto i (module_a->functions.begin ()), j (module_a->functions.end ()); i != j && result.error == nullptr; ++i)
    {
        
    }
    if (result.error == nullptr)
    {
        result.module = module;
    }
    return result;
}