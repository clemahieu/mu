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

static void print_module (llvm::Module * module, std::string & target)
{
    llvm::raw_string_ostream stream (target);
    module->print (stream, nullptr);
}

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

TEST (llvmc_generator, generate_parameter_return)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    function1.results.push_back (decltype (function1.results)::value_type ());
    auto & results1 (function1.results [0]);
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
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
    ASSERT_EQ (1, function2->getBasicBlockList().size ());
    auto block1 (function2->getBasicBlockList().begin ());
    ASSERT_EQ (2, block1->getInstList().size ());
    auto instructions (block1->getInstList ().begin ());
    auto instruction2 (llvm::cast <llvm::BinaryOperator> (instructions));
    ASSERT_EQ (llvm::Instruction::Add, instruction2->getOpcode ());
    ++instructions;
    llvm::cast <llvm::ReturnInst> (instructions);
    std::string info;
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}

TEST (llvmc_generator, generate_two_return)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    function1.results.push_back (decltype (function1.results)::value_type ());
    auto & results1 (function1.results [0]);
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
    results1.push_back (&result1);
    results1.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result->getFunctionList ().size ());
    llvm::Function * function2 (result->getFunctionList().begin ());
    auto struct1 (llvm::cast <llvm::StructType> (function2->getReturnType ()));
    auto element1 (struct1->element_begin ());
    auto type2 (llvm::cast <llvm::IntegerType> (*element1));
    ASSERT_EQ (1, type2->getBitWidth ());
    auto element2 (struct1->element_begin () + 1);
    auto type3 (llvm::cast <llvm::IntegerType> (*element2));
    ASSERT_EQ (1, type3->getBitWidth ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    ASSERT_TRUE (value1->getType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (value1->getType ())->getBitWidth ());
    ASSERT_EQ (1, function2->getBasicBlockList().size ());
    auto block1 (function2->getBasicBlockList().begin ());
    ASSERT_EQ (3, block1->getInstList().size ());
    auto instructions (block1->getInstList ().begin ());
    llvm::cast <llvm::InsertValueInst> (instructions);
    ++instructions;
    llvm::cast <llvm::InsertValueInst> (instructions);
    ++instructions;
    llvm::cast <llvm::ReturnInst> (instructions);
    std::string info;
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}

TEST (llvmc_generator, DISABLED_generate_if)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> predicates1;
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, &parameter1, predicates1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer1);
    function1.results.push_back (decltype (function1.results)::value_type ());
    auto & results1 (function1.results [0]);
    mu::llvmc::skeleton::result result1 (&element1.type_m, &element1);
    results1.push_back (&result1);
    function1.results.push_back (decltype (function1.results)::value_type ());
    auto & results2 (function1.results [1]);
    mu::llvmc::skeleton::result result2 (&element2.type_m, &element2);
    results2.push_back (&result2);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result->getFunctionList ().size ());
    llvm::Function * function2 (result->getFunctionList().begin ());
    ASSERT_TRUE (function2->getReturnType ()->isIntegerTy ());
    ASSERT_EQ (8, llvm::cast <llvm::IntegerType> (function2->getReturnType ())->getBitWidth ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    ASSERT_TRUE (value1->getType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (value1->getType ())->getBitWidth ());
    ASSERT_EQ (3, function2->getBasicBlockList ().size ());
    auto blocks (function2->getBasicBlockList ().begin ());
    auto block1 (blocks);
    ASSERT_EQ (1, block1->getInstList ().size ());
    llvm::cast <llvm::SwitchInst> (block1->getInstList ().begin ());
    ++blocks;
    auto block2 (blocks);
    ASSERT_EQ (1, block2->getInstList ().size ());
    llvm::cast <llvm::ReturnInst> (block2->getInstList ().begin ());
    ++blocks;
    auto block3 (blocks);
    ASSERT_EQ (1, block2->getInstList ().size ());
    llvm::cast <llvm::ReturnInst> (block3->getInstList ().begin ());
    std::string info;
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}