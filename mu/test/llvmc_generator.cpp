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
    std::string info;
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}

extern char const * const generate_empty_expected;

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
    std::string info;
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    print_module (result, info);
    ASSERT_EQ (std::string (generate_empty_expected), info);
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
    function1.branch_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
    function1.results.push_back (&result1);
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

extern char const * const generate_add_expected;

TEST (llvmc_generator, generate_add)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker add1 (mu::llvmc::instruction_type::add);
    arguments1.push_back (&add1);
    arguments1.push_back (&parameter1);
    arguments1.push_back (&parameter1);
    mu::llvmc::skeleton::instruction instruction1 (function1.entry, arguments1, 0 - 1);
    instruction1.predicate_position = 0 - 1;
    function1.branch_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result1 (&type1, &instruction1);
    function1.results.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_add_expected), info);
}

extern char const * const generate_two_return_expected;

TEST (llvmc_generator, generate_two_return)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    function1.branch_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
    function1.results.push_back (&result1);
    function1.results.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_two_return_expected), info);
}

extern char const * const generate_if_expected;

TEST (llvmc_generator, generate_if)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    arguments1.push_back (&marker1);
    arguments1.push_back (&parameter1);
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1, 0 - 1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    function1.branch_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result1 (&element1.type_m, &element1);
    function1.results.push_back (&result1);
    function1.branch_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&element2.type_m, &element2);
    function1.results.push_back (&result2);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result);
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_if_expected), info);
}

extern char const * const generate_if_value_expected;

TEST (llvmc_generator, generate_if_value)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    arguments1.push_back (&marker1);
    arguments1.push_back (&parameter1);
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1, 0 - 1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    function1.branch_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result1 (&element1.type_m, &element1);
    function1.results.push_back (&result1);
    mu::llvmc::skeleton::integer_type type2 (32);
    mu::llvmc::skeleton::constant_integer integer3 (32, 4);
    mu::llvmc::skeleton::result result3 (&type2, &integer3);
    function1.results.push_back (&result3);
    function1.branch_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&element2.type_m, &element2);
    function1.results.push_back (&result2);
    mu::llvmc::skeleton::constant_integer integer4 (32, 5);
    mu::llvmc::skeleton::result result4 (&type2, &integer4);
    function1.results.push_back (&result4);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result);
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_if_value_expected), info);
}

extern char const * const generate_if_join_expected;

TEST (llvm_generator, generate_if_join)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments2;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    arguments2.push_back (&marker1);
    arguments2.push_back (&parameter1);
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments2, 0 - 1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::vector <mu::llvmc::skeleton::value *> arguments1;
    arguments1.push_back (&element1);
    arguments1.push_back (&element2);
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments1, 0 - 1);
    mu::llvmc::skeleton::bottom_type bottom;
    mu::llvmc::skeleton::result result1 (&bottom, &join1);
    function1.branch_offsets.push_back (function1.results.size ());
    function1.results.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result);
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_if_join_expected), info);
}

extern char const * const generate_if_join_value_expected;

TEST (llvm_generator, generate_if_join_value)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    arguments1.push_back (&marker1);
    arguments1.push_back (&parameter1);
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1, 0 - 1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::add);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments2;
    arguments2.push_back (&marker2);
    arguments2.push_back (&parameter1);
    arguments2.push_back (&parameter1);
    arguments2.push_back (&element1);
    mu::llvmc::skeleton::instruction add1 (&branch1, arguments2, 3);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments3;
    arguments3.push_back (&marker2);
    arguments3.push_back (&parameter1);
    arguments3.push_back (&parameter1);
    arguments3.push_back (&element2);
    mu::llvmc::skeleton::instruction add2 (&branch2, arguments3, 3);
    
    mu::vector <mu::llvmc::skeleton::value *> arguments4;
    arguments4.push_back (&add1);
    arguments4.push_back (&add2);
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments4, 0 - 1);
    mu::llvmc::skeleton::result result1 (&type1, &join1);
    function1.branch_offsets.push_back (function1.results.size ());
    function1.results.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result);
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_if_join_value_expected), info);
}

extern char const * const generate_if_join_2value_expected;

TEST (llvm_generator, generate_if_join_2value)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    arguments1.push_back (&marker1);
    arguments1.push_back (&parameter1);
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1, 0 - 1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::add);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments2;
    arguments2.push_back (&marker2);
    arguments2.push_back (&parameter1);
    arguments2.push_back (&parameter1);
    arguments2.push_back (&element1);
    mu::llvmc::skeleton::instruction add1 (&branch1, arguments2, 3);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments3;
    arguments3.push_back (&marker2);
    arguments3.push_back (&parameter1);
    arguments3.push_back (&parameter1);
    arguments3.push_back (&element2);
    mu::llvmc::skeleton::instruction add2 (&branch2, arguments3, 3);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments4;
    arguments4.push_back (&marker2);
    arguments4.push_back (&parameter1);
    arguments4.push_back (&parameter1);
    arguments4.push_back (&element1);
    mu::llvmc::skeleton::instruction add3 (&branch1, arguments4, 3);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments5;
    arguments5.push_back (&marker2);
    arguments5.push_back (&parameter1);
    arguments5.push_back (&parameter1);
    arguments5.push_back (&element2);
    mu::llvmc::skeleton::instruction add4 (&branch2, arguments5, 3);
    
    mu::vector <mu::llvmc::skeleton::value *> arguments7;
    arguments7.push_back (&add1);
    arguments7.push_back (&add2);
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments7, 2);
    mu::llvmc::skeleton::result result1 (&type1, &join1);
    function1.branch_offsets.push_back (function1.results.size ());
    function1.results.push_back (&result1);
    mu::vector <mu::llvmc::skeleton::value *> arguments6;
    arguments6.push_back (&add3);
    arguments6.push_back (&add4);
    mu::llvmc::skeleton::join_value join2 (function1.entry, arguments6, 2);
    mu::llvmc::skeleton::result result2 (&type1, &join2);
    function1.results.push_back (&result2);
    
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result);
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_if_join_2value_expected), info);
}

extern char const * const generate_if_join_load_expected;

TEST (llvm_generator, generate_if_join_load)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::pointer_type type2 (&type1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    arguments1.push_back (&marker1);
    arguments1.push_back (&parameter1);
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1, 0 - 1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::load);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments2;
    arguments2.push_back (&marker2);
    mu::llvmc::skeleton::constant_pointer_null pointer1 (&type2);
    arguments2.push_back (&pointer1);
    arguments2.push_back (&element1);
    mu::llvmc::skeleton::instruction load1 (&branch1, arguments2, 2);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments3;
    arguments3.push_back (&marker2);
    mu::llvmc::skeleton::constant_pointer_null pointer2 (&type2);
    arguments3.push_back (&pointer2);
    arguments3.push_back (&element2);
    mu::llvmc::skeleton::instruction load2 (&branch2, arguments3, 2);
    
    mu::vector <mu::llvmc::skeleton::value *> arguments4;
    arguments4.push_back (&load1);
    arguments4.push_back (&load2);
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments4, 0 - 1);
    mu::llvmc::skeleton::result result1 (&type1, &join1);
    function1.branch_offsets.push_back (function1.results.size ());
    function1.results.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result);
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_if_join_load_expected), info);
}

extern char const * const generate_call_expected;

TEST (llvm_generator, generate_call)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
    function1.branch_offsets.push_back (function1.results.size ());
    function1.results.push_back (&result1);
    module.functions.push_back (&function1);
    mu::llvmc::skeleton::function function2 (module.global);
    mu::llvmc::skeleton::parameter parameter2 (function1.entry, &type1);
    function2.parameters.push_back (&parameter2);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&parameter2);
    mu::llvmc::skeleton::function_call call1 (&function1, function2.entry, arguments1);
    mu::llvmc::skeleton::call_element element1 (function2.entry, &call1, 0);
    call1.elements.push_back (&element1);
    mu::llvmc::skeleton::result result2 (&type1, &element1);
    function2.branch_offsets.push_back (function1.results.size ());
    function2.results.push_back (&result1);
    module.functions.push_back (&function2);
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result);
    std::string info;
    print_module (result, info);
    auto broken (llvm::verifyModule (*result, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_call_expected), info);
}