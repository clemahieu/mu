#include <gtest/gtest.h>

#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/generator.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

TEST (llvmc_generator, empty_module)
{
    mu::llvmc::ast::module module;
    mu::llvmc::generator generator;
    generator.generate (&module);
    ASSERT_NE (nullptr, generator.result.module);
    EXPECT_EQ (nullptr, generator.result.error);
    EXPECT_EQ (0, generator.result.module->getFunctionList ().size ());
}

TEST (llvmc_generator, one_function)
{
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function1;
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    generator.generate (&module);
    EXPECT_NE (nullptr, generator.result.module);
    EXPECT_EQ (nullptr, generator.result.error);
    ASSERT_EQ (1, generator.result.module->getFunctionList ().size ());
    auto function2 (generator.result.module->getFunctionList ().begin ());
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->getArgumentList ().size ());
    ASSERT_EQ (llvm::FunctionType::get (llvm::StructType::get (generator.context), false), function2->getFunctionType ());
}