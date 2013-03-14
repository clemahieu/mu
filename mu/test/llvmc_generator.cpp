#include <gtest/gtest.h>

#include <mu/llvmc/skeleton.hpp>
#include <mu/llvmc/generator.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/LLVMContext.h>

TEST (llvmc_generator, generate1)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (0, result->getFunctionList ().size ());
}