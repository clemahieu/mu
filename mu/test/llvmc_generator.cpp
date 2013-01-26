#include <gtest/gtest.h>

#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/generator.hpp>
#include <mu/llvmc/wrapper.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

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
    ASSERT_EQ (llvm::FunctionType::get (llvm::StructType::get (generator.context, llvm::ArrayRef <llvm::Type *> (llvm::Type::getInt8Ty (generator.context))), false), function2->getFunctionType ());
}

TEST (llvmc_generator, passthrough_function)
{
    mu::llvmc::generator generator;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function1;
    mu::llvmc::wrapper::type type1 (llvm::Type::getInt1Ty (generator.context));
    mu::llvmc::ast::argument argument1 (&type1);
    function1.parameters.push_back (&argument1);
    function1.results.push_back (decltype (function1.results)::value_type ());
    ASSERT_EQ (1, function1.results.size ());
    auto & results0 (function1.results [0]);
    mu::llvmc::ast::result result1 (&type1);
    result1.value = &argument1;
    results0.push_back (&result1);
    module.functions.push_back (&function1);
    generator.generate (&module);
    EXPECT_NE (nullptr, generator.result.module);
    EXPECT_EQ (nullptr, generator.result.error);
    ASSERT_EQ (1, generator.result.module->getFunctionList ().size ());
    auto function2 (generator.result.module->getFunctionList ().begin ());
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto argument2 (function2->getArgumentList ().begin ());
    ASSERT_EQ (type1.type_m, argument2->getType ());
    ASSERT_EQ (llvm::Type::getInt1Ty (generator.context), function2->getArgumentList ().begin ()->getType ());
    std::vector <llvm::Type *> types;
    types.push_back (llvm::Type::getInt8Ty (generator.context));
    types.push_back (llvm::Type::getInt1Ty (generator.context));
    ASSERT_EQ (llvm::StructType::get (generator.context, types), function2->getReturnType ());
    ASSERT_EQ (1, function2->getBasicBlockList ().size ());
    auto block1 (function2->getBasicBlockList().begin ());
    ASSERT_EQ (3, block1->getInstList().size ());
    auto inst1 (block1->getInstList().begin ());
    ++++inst1;
    auto ret1 (llvm::dyn_cast <llvm::ReturnInst> (inst1));
    ASSERT_NE (nullptr, ret1);
}

TEST (llvmc_generator, passthrough_function2)
{
    mu::llvmc::generator generator;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function1;
    mu::llvmc::wrapper::type type1 (llvm::Type::getInt1Ty (generator.context));
    mu::llvmc::ast::argument argument1 (&type1);
    function1.parameters.push_back (&argument1);
    mu::llvmc::ast::argument argument2 (&type1);
    function1.parameters.push_back (&argument2);
    function1.results.push_back (decltype (function1.results)::value_type ());
    ASSERT_EQ (1, function1.results.size ());
    auto & results0 (function1.results [0]);
    mu::llvmc::ast::result result1 (&type1);
    result1.value = &argument1;
    results0.push_back (&result1);
    mu::llvmc::ast::result result2 (&type1);
    result2.value = &argument2;
    results0.push_back (&result2);
    module.functions.push_back (&function1);
    generator.generate (&module);
    EXPECT_NE (nullptr, generator.result.module);
    EXPECT_EQ (nullptr, generator.result.error);
    ASSERT_EQ (1, generator.result.module->getFunctionList ().size ());
    auto function2 (generator.result.module->getFunctionList ().begin ());
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (2, function2->getArgumentList ().size ());
    auto argument3 (function2->getArgumentList ().begin ());
    ASSERT_EQ (type1.type_m, argument3->getType ());
    auto argument4 (++function2->getArgumentList().begin ());
    ASSERT_EQ (type1.type_m, argument4->getType ());
    ASSERT_EQ (llvm::Type::getInt1Ty (generator.context), function2->getArgumentList ().begin ()->getType ());
    std::vector <llvm::Type *> types;
    types.push_back (llvm::Type::getInt8Ty (generator.context));
    types.push_back (llvm::Type::getInt1Ty (generator.context));
    types.push_back (llvm::Type::getInt1Ty (generator.context));
    ASSERT_EQ (llvm::StructType::get (generator.context, types), function2->getReturnType ());
    ASSERT_EQ (1, function2->getBasicBlockList ().size ());
    auto block1 (function2->getBasicBlockList().begin ());
    ASSERT_EQ (4, block1->getInstList().size ());
    auto inst1 (block1->getInstList().begin ());
    ++++++inst1;
    auto ret1 (llvm::dyn_cast <llvm::ReturnInst> (inst1));
    ASSERT_NE (nullptr, ret1);
}