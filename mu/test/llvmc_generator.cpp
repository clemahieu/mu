#include <gtest/gtest.h>

#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/generator.hpp>

TEST (llvmc_generator, empty_module)
{
    mu::llvmc::ast::module module;
    mu::llvmc::generator generator;
    auto module1 (generator.generate (&module));
    EXPECT_NE (nullptr, module1.module);
    EXPECT_EQ (nullptr, module1.error);
}