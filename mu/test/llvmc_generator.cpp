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
#include <llvm/ExecutionEngine/ExecutionEngine.h>

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

extern char const * const generate_parameter_expected;

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
    print_module (result.module, info);
    ASSERT_EQ (std::string (generate_parameter_expected), info);
}

TEST (llvmc_generator, generate_pointer_type)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::pointer_type type2 (&type1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type2);
    function1.parameters.push_back (&parameter1);
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    ASSERT_EQ (1, result.module->getFunctionList ().size ());
    llvm::Function * function2 (result.module->getFunctionList().begin ());
    ASSERT_TRUE (function2->getReturnType ()->isVoidTy ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    auto type3 (llvm::cast <llvm::PointerType> (value1->getType ()));
    auto type4 (llvm::cast <llvm::IntegerType> (type3->getElementType()));
    ASSERT_EQ (1, type4->getBitWidth ());
    std::string info;
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
}

extern char const * const generate_parameter_return_expected;

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
    ASSERT_NE (result.names.end (), result.names.find (U"0"));
    auto function2 (result.names.find (U"0")->second);
    ASSERT_TRUE (function2->getReturnType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (function2->getReturnType ())->getBitWidth ());
    ASSERT_EQ (1, function2->getArgumentList ().size ());
    auto const & value1 (function2->getArgumentList ().begin ());
    ASSERT_TRUE (value1->getType ()->isIntegerTy ());
    ASSERT_EQ (1, llvm::cast <llvm::IntegerType> (value1->getType ())->getBitWidth ());
    std::string info;
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    print_module (result.module, info);
    ASSERT_EQ (std::string (generate_parameter_return_expected), info);
    llvm::EngineBuilder builder (result.module);
    auto engine (builder.create ());
    auto function3 (engine->getPointerToFunction (function2));
    auto function4 (reinterpret_cast <bool (*) (bool)> (function3));
    auto result_false (function4 (false));
    ASSERT_EQ (false, result_false);
    auto result_true (function4 (true));
    ASSERT_EQ (true, result_true);
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
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    print_module (result.module, info);
    ASSERT_EQ (std::string (generate_add_expected), info);
    llvm::EngineBuilder builder (result.module);
    auto engine (builder.create ());
    ASSERT_NE (result.names.end (), result.names.find (U"0"));
    auto function2 (engine->getPointerToFunction (result.names.find (U"0")->second));
    auto function3 (reinterpret_cast <bool (*) (bool)> (function2));
    auto result_false (function3 (0));
    ASSERT_EQ (0, result_false);
    auto result_true (function3 (1));
    ASSERT_EQ (0, result_true);
}

extern char const * const generate_sub_expected;

TEST (llvmc_generator, generate_sub)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker sub1 (mu::llvmc::instruction_type::sub);
    arguments1.push_back (&sub1);
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
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    print_module (result.module, info);
    ASSERT_EQ (std::string (generate_sub_expected), info);
    llvm::EngineBuilder builder (result.module);
    auto engine (builder.create ());
    ASSERT_NE (result.names.end (), result.names.find (U"0"));
    auto function2 (engine->getPointerToFunction (result.names.find (U"0")->second));
    auto function3 (reinterpret_cast <bool (*) (bool)> (function2));
    auto result_false (function3 (0));
    ASSERT_EQ (0, result_false);
    auto result_true (function3 (1));
    ASSERT_EQ (0, result_true);
}

extern char const * const generate_store_expected;

TEST (llvmc_generator, generate_store)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::pointer_type type2 (&type1);
    mu::llvmc::skeleton::parameter parameter2 (function1.entry, &type2);
    function1.parameters.push_back (&parameter2);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker add1 (mu::llvmc::instruction_type::store);
    arguments1.push_back (&add1);
    arguments1.push_back (&parameter1);
    arguments1.push_back (&parameter2);
    mu::llvmc::skeleton::instruction instruction1 (function1.entry, arguments1, arguments1.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&instruction1);
    function1.branch_ends.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_store_expected), info);
    llvm::EngineBuilder builder (result.module);
    auto engine (builder.create ());
    ASSERT_NE (result.names.end (), result.names.find (U"0"));
    auto function2 (engine->getPointerToFunction (result.names.find (U"0")->second));
    auto function3 (reinterpret_cast <void (*) (bool, bool*)> (function2));
    auto val1 (false);
    function3 (true, &val1);
    ASSERT_EQ (true, val1);
    auto val2 (true);
    function3 (false, &val2);
    ASSERT_EQ (false, val2);
}

extern char const * const generate_load_expected;

TEST (llvmc_generator, generate_load)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::pointer_type type2 (&type1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type2);
    function1.parameters.push_back (&parameter1);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker add1 (mu::llvmc::instruction_type::load);
    arguments1.push_back (&add1);
    arguments1.push_back (&parameter1);
    mu::llvmc::skeleton::instruction instruction1 (function1.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::result result1 (&type1, &instruction1);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_load_expected), info);
    llvm::EngineBuilder builder (result.module);
    auto engine (builder.create ());
    ASSERT_NE (result.names.end (), result.names.find (U"0"));
    auto function2 (engine->getPointerToFunction (result.names.find (U"0")->second));
    auto function3 (reinterpret_cast <bool (*) (bool*)> (function2));
    auto val1 (false);
    function3 (&val1);
    ASSERT_EQ (false, val1);
    auto val2 (true);
    function3 (&val2);
    ASSERT_EQ (true, val2);
}

extern char const * const generate_icmp1_expected;

TEST (llvmc_generator, generate_icmp1)
{
    llvm::LLVMContext context;
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::parameter parameter2 (function1.entry, &type1);
    function1.parameters.push_back (&parameter2);
    mu::vector <mu::llvmc::skeleton::node *> arguments1;
    mu::llvmc::skeleton::marker icmp1 (mu::llvmc::instruction_type::icmp);
    arguments1.push_back (&icmp1);
	mu::llvmc::skeleton::predicate predicate1 (mu::llvmc::predicates::icmp_eq);
	arguments1.push_back (&predicate1);
    arguments1.push_back (&parameter1);
    arguments1.push_back (&parameter2);
    mu::llvmc::skeleton::instruction instruction1 (function1.entry, arguments1, arguments1.size ());
    mu::llvmc::skeleton::result result1 (&type1, &instruction1);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    module.functions [U"0"] = &function1;
    mu::llvmc::generator generator;
    auto result (generator.generate (context, &module));
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_icmp1_expected), info);
    llvm::EngineBuilder builder (result.module);
    auto engine (builder.create ());
    ASSERT_NE (result.names.end (), result.names.find (U"0"));
    auto function2 (engine->getPointerToFunction (result.names.find (U"0")->second));
    auto function3 (reinterpret_cast <bool (*) (bool, bool)> (function2));
    auto result2 (function3 (false, false));
    ASSERT_EQ (true, result2);
    auto result3 (function3 (false, true));
    ASSERT_EQ (false, result3);
    auto result4 (function3 (true, false));
    ASSERT_EQ (false, result4);
    auto result5 (function3 (true, true));
    ASSERT_EQ (true, result5);
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
    llvm::EngineBuilder builder (result.module);
    auto engine (builder.create ());
    ASSERT_NE (result.names.end (), result.names.find (U"0"));
    auto function2 (engine->getPointerToFunction (result.names.find (U"0")->second));
	struct thing
	{
		bool b0;
		bool b1;
	};
    auto function3 (reinterpret_cast <thing (*) (bool)> (function2));
    /*auto result2 (function3 (false));
    ASSERT_EQ (false, result2.b0);
    ASSERT_EQ (false, result2.b1);
    auto result3 (function3 (true));
    ASSERT_EQ (true, result3.b0);
    ASSERT_EQ (true, result3.b1);*/
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::result result1 (&mu::llvmc::skeleton::the_unit_type, &element1);
    function1.results.push_back (&result1);
    mu::llvmc::skeleton::integer_type type2 (32);
    mu::llvmc::skeleton::constant_integer integer3 (module.global, 32, 4);
    mu::llvmc::skeleton::result result3 (&type2, &integer3);
    function1.results.push_back (&result3);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&mu::llvmc::skeleton::the_unit_type, &element2);
    function1.results.push_back (&result2);
    mu::llvmc::skeleton::constant_integer integer4 (module.global, 32, 5);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::load);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments2;
    arguments2.push_back (&marker2);
    mu::llvmc::skeleton::constant_pointer_null pointer1 (module.global, &type2);
    arguments2.push_back (&pointer1);
    arguments2.push_back (&element1);
    mu::llvmc::skeleton::instruction load1 (&branch1, arguments2, 2);
    
    mu::vector <mu::llvmc::skeleton::node *> arguments3;
    arguments3.push_back (&marker2);
    mu::llvmc::skeleton::constant_pointer_null pointer2 (module.global, &type2);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
    mu::llvmc::skeleton::switch_element element1 (&branch1, &instruction1, &integer1);
    mu::llvmc::skeleton::branch branch2 (function1.entry);
    mu::llvmc::skeleton::constant_integer integer2 (module.global, 1, 1);
    mu::llvmc::skeleton::switch_element element2 (&branch2, &instruction1, &integer2);
    mu::llvmc::skeleton::result result1 (&mu::llvmc::skeleton::the_unit_type, &element1);
    function1.results.push_back (&result1);
    mu::llvmc::skeleton::constant_integer constant1 (module.global, 32, 1);
    mu::llvmc::skeleton::result result5 (&type2, &constant1);
    function1.results.push_back (&result5);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::skeleton::result result2 (&mu::llvmc::skeleton::the_unit_type, &element2);
    function1.results.push_back (&result2);
    mu::llvmc::skeleton::constant_integer constant2 (module.global, 32, 2);
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
    mu::llvmc::skeleton::constant_integer integer1 (module.global, 1, 0);
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

extern char const * const generate_loop1_expected;

TEST (llvm_generator, generate_loop1)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (1);
	mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
	function1.parameters.push_back (&parameter1);
	mu::llvmc::skeleton::loop loop1;
	mu::llvmc::skeleton::branch loop_entry_branch (function1.entry);
	loop1.loop_entry_branch = &loop_entry_branch;
	loop1.arguments.push_back (&parameter1);
	loop1.set_argument_predicate_offset ();
	ASSERT_EQ (loop1.arguments.size (), loop1.argument_predicate_offset);
	mu::llvmc::skeleton::loop_parameter loop_parameter1 (loop1.loop_entry_branch, &type1);
	loop1.parameters.push_back (&loop_parameter1);
	mu::vector <mu::llvmc::skeleton::node *> arguments1;
	mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::icmp);
	arguments1.push_back (&marker1);
	mu::llvmc::skeleton::predicate predicate1 (mu::llvmc::predicates::icmp_eq);
	arguments1.push_back (&predicate1);
	arguments1.push_back (&loop_parameter1);
	mu::llvmc::skeleton::constant_integer constant_integer1 (module.global, 1, 0);
	arguments1.push_back (&constant_integer1);
	mu::llvmc::skeleton::instruction instruction1 (loop1.loop_entry_branch, arguments1, arguments1.size ());
	mu::vector <mu::llvmc::skeleton::node *> arguments2;
	mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::if_i);
	arguments2.push_back (&marker2);
	arguments2.push_back (&instruction1);
	mu::llvmc::skeleton::switch_i switch1 (loop1.loop_entry_branch, arguments2);
	mu::llvmc::skeleton::constant_integer constant_integer2 (module.global, 1, 0);
	mu::llvmc::skeleton::switch_element element1 (loop1.loop_entry_branch, &switch1, &constant_integer2);
	switch1.elements.push_back (&element1);
	mu::llvmc::skeleton::constant_integer constant_integer3 (module.global, 1, 1);
	mu::llvmc::skeleton::switch_element element2 (loop1.loop_entry_branch, &switch1, &constant_integer3);
	switch1.elements.push_back (&element2);
	mu::vector <mu::llvmc::skeleton::node *> arguments3;
	mu::llvmc::skeleton::marker marker3 (mu::llvmc::instruction_type::add);
	arguments3.push_back (&marker3);
	arguments3.push_back (&loop_parameter1);
	arguments3.push_back (&constant_integer3);
	mu::llvmc::skeleton::instruction instruction2 (loop1.loop_entry_branch, arguments3, arguments3.size ());
	loop1.results.push_back (&instruction2);
	loop1.predicate_offsets.push_back (loop1.results.size ());
	loop1.results.push_back (&element1);
	loop1.branch_ends.push_back (loop1.results.size ());
	loop1.predicate_offsets.push_back (loop1.results.size ());
	loop1.results.push_back (&element1);
	loop1.branch_ends.push_back (loop1.results.size ());
	mu::llvmc::skeleton::loop_element_unit element3 (function1.entry, &loop1, 1);
	loop1.elements.push_back (&element3);
	function1.predicate_offsets.push_back (function1.results.size ());
	function1.results.push_back (&element3);
	function1.branch_ends.push_back (function1.results.size ());
	module.functions [U"0"] = &function1;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_loop1_expected), info);
}

extern char const * const generate_loop_count_expected;

TEST (llvm_generator, DISABLED_generate_loop_count)
{
    mu::llvmc::skeleton::module module;
    mu::llvmc::skeleton::function function1 (module.global);
    mu::llvmc::skeleton::integer_type type1 (32);
	mu::llvmc::skeleton::parameter parameter1 (function1.entry, &type1);
	function1.parameters.push_back (&parameter1);
	mu::llvmc::skeleton::loop loop1;
	mu::llvmc::skeleton::branch loop_entry_branch (function1.entry);
	loop1.loop_entry_branch = &loop_entry_branch;
	loop1.arguments.push_back (&parameter1);
	mu::llvmc::skeleton::constant_integer constant_integer1 (module.global, 32, 0);
	loop1.arguments.push_back (&constant_integer1);
	loop1.set_argument_predicate_offset ();
	mu::llvmc::skeleton::loop_parameter loop_parameter1 (loop1.loop_entry_branch, &type1); // Count down
	mu::llvmc::skeleton::loop_parameter loop_parameter2 (loop1.loop_entry_branch, &type1); // Count up
	loop1.parameters.push_back (&loop_parameter1);
	loop1.parameters.push_back (&loop_parameter2);	
	mu::vector <mu::llvmc::skeleton::node *> arguments1;
	mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::icmp);
	arguments1.push_back (&marker1);
	mu::llvmc::skeleton::predicate predicate1 (mu::llvmc::predicates::icmp_eq);
	arguments1.push_back (&predicate1);
	arguments1.push_back (&loop_parameter1);
	arguments1.push_back (&constant_integer1);
	mu::llvmc::skeleton::instruction instruction1 (loop1.loop_entry_branch, arguments1, arguments1.size ());
	mu::llvmc::skeleton::integer_type type2 (1);
	mu::vector <mu::llvmc::skeleton::node *> arguments2;
	mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::switch_i);
	arguments2.push_back (&marker2);
	arguments2.push_back (&instruction1);
	mu::llvmc::skeleton::constant_integer constant_integer2 (module.global, 1, 0);
	arguments2.push_back (&constant_integer2);
	mu::llvmc::skeleton::constant_integer constant_integer3 (module.global, 1, 1);
	arguments2.push_back (&constant_integer3);
	mu::llvmc::skeleton::switch_i switch1 (loop1.loop_entry_branch, arguments2);
	mu::llvmc::skeleton::branch branch1 (loop1.loop_entry_branch);
	mu::llvmc::skeleton::branch branch2 (loop1.loop_entry_branch);
	mu::llvmc::skeleton::switch_element element1 (&branch1, &switch1, &constant_integer2);
	mu::llvmc::skeleton::switch_element element2 (&branch2, &switch1, &constant_integer3);
	mu::vector <mu::llvmc::skeleton::node *> arguments3;

	module.functions [U"0"] = &function1;
    
    mu::llvmc::generator generator;
    llvm::LLVMContext context;
    auto result (generator.generate (context, &module));
    ASSERT_NE (nullptr, result.module);
    std::string info;
    print_module (result.module, info);
    auto broken (llvm::verifyModule (*result.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
    ASSERT_TRUE (!broken);
    ASSERT_EQ (std::string (generate_loop_count_expected), info);
}