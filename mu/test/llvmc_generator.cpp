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
    ASSERT_EQ (0, result.module->getFunctionList ().size ());
    std::string info;
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}

extern char const * const generate_empty_expected;

TEST (llvmc_generator, generate_empty)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result.names.size ());
    ASSERT_EQ (1, result.module->getFunctionList ().size ());
    llvm::Function * function2 (result.module->getFunctionList().begin ());
    ASSERT_EQ (function2, result.names [U"0"]);
    ASSERT_TRUE (function2->getReturnType ()->isVoidTy ());
    ASSERT_TRUE (function2->getArgumentList ().empty ());
    std::string info;
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    print_module (result.module, info);
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
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result.module->getFunctionList ().size ());
    llvm::Function * function2 (result.module->getFunctionList().begin ());
    ASSERT_TRUE (function2->getReturnType ()->isVoidTy ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    ASSERT_TRUE (value1->getType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (value1->getType ())->getBitWidth ());
    std::string info;
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result.module->getFunctionList ().size ());
    llvm::Function * function2 (result.module->getFunctionList().begin ());
    ASSERT_TRUE (function2->getReturnType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (function2->getReturnType ())->getBitWidth ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    ASSERT_TRUE (value1->getType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (value1->getType ())->getBitWidth ());
    std::string info;
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::instruction instruction1 (function1.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::result result1 (&type1, &instruction1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
    function1.results.push_back (&result1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::result result1 (&mu::llvmc::skeleton::the_unit_type, &element1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&mu::llvmc::skeleton::the_unit_type, &element2);
    function1.results.push_back (&result2);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::result result1 (&mu::llvmc::skeleton::the_unit_type, &element1);
    function1.results.push_back (&result1);
    mu::llvmc::skeleton::integer_type type2 (32);
    mu::llvmc::skeleton::constant_integer integer3 (32, 4);
    mu::llvmc::skeleton::result result3 (&type2, &integer3);
    function1.results.push_back (&result3);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&mu::llvmc::skeleton::the_unit_type, &element2);
    function1.results.push_back (&result2);
    mu::llvmc::skeleton::constant_integer integer4 (32, 5);
    mu::llvmc::skeleton::result result4 (&type2, &integer4);
    function1.results.push_back (&result4);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments2);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::vector <mu::llvmc::skeleton::value *> arguments1;
    arguments1.push_back (&element1);
    arguments1.push_back (&element2);
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments1);
    mu::llvmc::skeleton::unit_type unit;
    mu::llvmc::skeleton::result result1 (&unit, &join1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1);
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
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments4);
    mu::llvmc::skeleton::result result1 (&type1, &join1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1);
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
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments7);
    mu::llvmc::skeleton::result result1 (&type1, &join1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::vector <mu::llvmc::skeleton::value *> arguments6;
    arguments6.push_back (&add3);
    arguments6.push_back (&add4);
    mu::llvmc::skeleton::join_value join2 (function1.entry, arguments6);
    mu::llvmc::skeleton::result result2 (&type1, &join2);
    function1.results.push_back (&result2);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
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
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments1);
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
    mu::llvmc::skeleton::join_value join1 (function1.entry, arguments4);
    mu::llvmc::skeleton::result result1 (&type1, &join1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_if_join_load_expected), info);
}

extern char const * const generate_call_0_expected;

TEST (llvm_generator, generate_call_0)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::unit_type type1;
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    
    mu::llvmc::skeleton::function function2 (module.global);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&function1);
    mu::llvmc::skeleton::function_call call1 (&function1, function2.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::call_element_value element1 (function2.entry, &call1, 0);
    call1.elements.push_back (&element1);
    mu::llvmc::skeleton::result result2 (&type1, &element1);
    function2.results.push_back (&result2);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    module.functions [U"1"] = &function2;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_call_0_expected), info);
}

extern char const * const generate_call_1_expected;

TEST (llvm_generator, generate_call_1)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::result result1 (&type1, &parameter1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    
    mu::llvmc::skeleton::function function2 (module.global);
    mu::llvmc::skeleton::parameter parameter2 (function1.entry, &type1);
    function2.parameters.push_back (&parameter2);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&function1);
    arguments1.push_back (&parameter2);
    mu::llvmc::skeleton::function_call call1 (&function1, function2.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::call_element_value element1 (function2.entry, &call1, 0);
    call1.elements.push_back (&element1);
    mu::llvmc::skeleton::result result2 (&type1, &element1);
    function2.results.push_back (&result2);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"1"] = &function2;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_call_1_expected), info);
}

extern char const * const generate_call_2_expected;

TEST (llvm_generator, generate_call_2)
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
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments2);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::result result1 (&mu::llvmc::skeleton::the_unit_type, &element1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&mu::llvmc::skeleton::the_unit_type, &element2);
    function1.results.push_back (&result2);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    
    mu::llvmc::skeleton::function function2 (module.global);
    mu::llvmc::skeleton::parameter parameter2 (function1.entry, &type1);
    function2.parameters.push_back (&parameter2);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&function1);
    arguments1.push_back (&parameter2);
    mu::llvmc::skeleton::function_call call1 (&function1, function2.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::call_element_value element3 (function2.entry, &call1, 0);
    call1.elements.push_back (&element3);
    mu::llvmc::skeleton::call_element_value element4 (function2.entry, &call1, 0);
    call1.elements.push_back (&element4);
    mu::llvmc::skeleton::result result3 (element3.type (), &element3);
    function2.results.push_back (&result3);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    mu::llvmc::skeleton::result result4 (element4.type (), &element4);
    function2.results.push_back (&result4);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    module.functions [U"1"] = &function2;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_call_2_expected), info);
}

extern char const * const generate_call_3_expected;

TEST (llvm_generator, generate_call_3)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::integer_type type2 (32);
    mu::vector <mu::llvmc::skeleton::node *> arguments2;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    arguments2.push_back (&marker1);
    arguments2.push_back (&parameter1);
    mu::llvmc::skeleton::switch_i instruction1 (function1.entry, arguments2);
    mu::llvmc::skeleton::branch branch1 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::result result1 (&mu::llvmc::skeleton::the_unit_type, &element1);
    function1.results.push_back (&result1);
    mu::llvmc::skeleton::constant_integer constant1 (32, 1);
    mu::llvmc::skeleton::result result5 (&type2, &constant1);
    function1.results.push_back (&result5);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&mu::llvmc::skeleton::the_unit_type, &element2);
    function1.results.push_back (&result2);
    mu::llvmc::skeleton::constant_integer constant2 (32, 2);
    mu::llvmc::skeleton::result result6 (&type2, &constant2);
    function1.results.push_back (&result6);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    
    mu::llvmc::skeleton::function function2 (module.global);
    mu::llvmc::skeleton::parameter parameter2 (function1.entry, &type1);
    function2.parameters.push_back (&parameter2);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&function1);
    arguments1.push_back (&parameter2);
    mu::llvmc::skeleton::function_call call1 (&function1, function2.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::call_element_value element3 (function2.entry, &call1, 0);
    call1.elements.push_back (&element3);
    mu::llvmc::skeleton::call_element_value element4 (function2.entry, &call1, 0);
    call1.elements.push_back (&element4);
    mu::llvmc::skeleton::result result3 (element3.type (), &element3);
    function2.results.push_back (&result3);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    mu::llvmc::skeleton::result result4 (element4.type (), &element4);
    function2.results.push_back (&result4);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    module.functions [U"1"] = &function2;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_call_3_expected), info);
}

extern char const * const generate_call_predicate_b1v0_expected;

TEST (llvm_generator, generate_call_predicate_b1v0)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::unit_type type1;
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&module.the_unit_value);
    function1.branch_ends.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    
    mu::llvmc::skeleton::function function2 (module.global);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&function1);
    mu::llvmc::skeleton::function_call call1 (&function1, function2.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::call_element_value element1 (function2.entry, &call1, 0);
    call1.elements.push_back (&element1);
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&element1);
    function2.branch_ends.push_back (function2.results.size ());
    module.functions [U"1"] = &function2;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_call_predicate_b1v0_expected), info);
}

extern char const * const generate_call_predicate_b1v1_expected;

TEST (llvm_generator, generate_call_predicate_b1v1)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::unit_type type1;
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&module.the_unit_value);
    function1.branch_ends.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    
    mu::llvmc::skeleton::function function2 (module.global);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    arguments1.push_back (&function1);
    mu::llvmc::skeleton::function_call call1 (&function1, function2.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::call_element_value element1 (function2.entry, &call1, 0);
    call1.elements.push_back (&element1);
    mu::llvmc::skeleton::integer_type type2 (1);
    mu::llvmc::skeleton::constant_integer integer1 (1, 0);
    mu::llvmc::skeleton::result result1 (&type2, &integer1);
    function2.results.push_back (&result1);
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&element1);
    function2.branch_ends.push_back (function2.results.size ());
    module.functions [U"1"] = &function2;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_call_predicate_b1v1_expected), info);
}