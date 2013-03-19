#include <gtest/gtest.h>

#include <mu/llvmc/skeleton.hpp>
#include <mu/llvmc/generator.hpp>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/LLVMContext.h>
#include <llvm/Function.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/raw_ostream.h>

TEST (llvmc_generator, generate1)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (0, result->getFunctionList ().size ());
}

TEST (llvmc_generator, generate_empty)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result->getFunctionList ().size ());
    llvm::Function * function2 (result->getFunctionList().begin ());
    ASSERT_TRUE (function2->getReturnType ()->isVoidTy ());
    ASSERT_TRUE (function2->getArgumentList ().empty ());
}

TEST (llvmc_generator, generate_parameter)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result->getFunctionList ().size ());
    llvm::Function * function2 (result->getFunctionList().begin ());
    ASSERT_TRUE (function2->getReturnType ()->isVoidTy ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    ASSERT_TRUE (value1->getType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (value1->getType ())->getBitWidth ());
    std::string info;
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}

TEST (llvmc_generator, generate_add)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&parameter1);
    arguments1.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> predicates1;
    mu::llvmc::skeleton::instruction instruction1 (function1.entry, arguments1, predicates1, mu::llvmc::instruction_type::add);
    function1.results.push_back (decltype (function1.results)::value_type ());
    auto & results1 (function1.results [0]);
    mu::llvmc::skeleton::result result1 (&type1, &instruction1);
    results1.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result->getFunctionList ().size ());
    llvm::Function * function2 (result->getFunctionList().begin ());
    ASSERT_TRUE (function2->getReturnType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (function2->getReturnType ())->getBitWidth ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    ASSERT_TRUE (value1->getType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (value1->getType ())->getBitWidth ());
    std::string info;
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}