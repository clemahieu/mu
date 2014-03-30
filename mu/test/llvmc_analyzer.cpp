#include <gtest/gtest.h>

#include <mu/llvmc/analyzer.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/skeleton.hpp>
#include <mu/core/error.hpp>
#include <mu/llvmc/ast_t.hpp>
#include <mu/llvmc/parser.hpp>

static mu::core::region empty_region (0, 0, 0, 0, 0, 0);

TEST (llvmc_ast, iteration)
{
    mu::llvmc::ast::function function1 (nullptr);
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++result_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++predicate_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++transition_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++branch_calls;},
                                [&]
                                ()
    {++loop_calls; return true;});
    ASSERT_EQ (0, result_calls);
    ASSERT_EQ (0, predicate_calls);
    ASSERT_EQ (0, transition_calls);
    ASSERT_EQ (0, branch_calls);
    ASSERT_EQ (0, loop_calls);
}

TEST (llvmc_ast, iteration_one_result)
{
    mu::llvmc::ast::function function1 (nullptr);
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::result result1 (&value1, nullptr);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++result_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++predicate_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++transition_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
    {++branch_calls;},
                                [&]
                                ()
    {++loop_calls; return true;});
    EXPECT_EQ (1, result_calls);
    EXPECT_EQ (0, predicate_calls);
    EXPECT_EQ (1, transition_calls);
    EXPECT_EQ (1, branch_calls);
    EXPECT_EQ (1, loop_calls);
}

TEST (llvmc_ast, iteration_one_predicate)
{
    mu::llvmc::ast::function function1 (nullptr);
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    mu::llvmc::ast::unit unit1 (nullptr);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++result_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++predicate_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++transition_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++branch_calls;},
                                [&]
                                ()
                                {++loop_calls; return true;});
    EXPECT_EQ (0, result_calls);
    EXPECT_EQ (1, predicate_calls);
    EXPECT_EQ (1, transition_calls);
    EXPECT_EQ (1, branch_calls);
    EXPECT_EQ (1, loop_calls);
}

TEST (llvmc_ast, iteration_multi_predicate)
{
    mu::llvmc::ast::function function1 (nullptr);
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    mu::llvmc::ast::unit unit1 (nullptr);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.results.push_back (&unit1);
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++result_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++predicate_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++transition_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++branch_calls;},
                                [&]
                                ()
                                {++loop_calls; return true;});
    EXPECT_EQ (0, result_calls);
    EXPECT_EQ (3, predicate_calls);
    EXPECT_EQ (1, transition_calls);
    EXPECT_EQ (1, branch_calls);
    EXPECT_EQ (3, loop_calls);
}

TEST (llvmc_ast, iterate_function)
{
    mu::llvmc::ast::function function1 (nullptr);
    mu::llvmc::ast::function function2 (nullptr);
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&function2);
    function1.branch_ends.push_back (function1.results.size ());
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++result_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++predicate_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++transition_calls;},
                                [&]
                                (mu::llvmc::ast::node *, size_t)
                                {++branch_calls;},
                                [&]
                                ()
                                {++loop_calls; return true;});
    EXPECT_EQ (0, result_calls);
    EXPECT_EQ (1, predicate_calls);
    EXPECT_EQ (1, transition_calls);
    EXPECT_EQ (1, branch_calls);
    EXPECT_EQ (1, loop_calls);
}

TEST (llvmc_analyzer, empty)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module (nullptr);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (0, result.module->globals.size ());
}

TEST (llvmc_analyzer, fail_not_module)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::unit node (nullptr);
    auto result (analyzer.analyze (&node));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, function_already_named)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    mu::llvmc::ast::element element2 (&function, 0, 1, U"1", mu::empty_region);
    module.globals.push_back (&element2);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
	ASSERT_EQ (1, result.module->globals.size ());
	auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
	ASSERT_NE (nullptr, function1);
	ASSERT_EQ (U"0", function1->name);
}

TEST (llvmc_analyzer, empty_function)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
	module.names [U"0"] = &element1;
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
	ASSERT_EQ (function.region, function1->region);
	ASSERT_EQ (1, module.names.size ());
	ASSERT_NE (module.names.end (), module.names.find (U"0"));
    ASSERT_NE (result.module->names.end (), result.module->names.find (U"0"));
    ASSERT_NE (nullptr, (*result.module) [U"0"]);
}

TEST (llvmc_analyzer, name_with_set)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
	mu::llvmc::ast::set set1;
	set1.nodes.push_back (&element1);
    module.globals.push_back (&set1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
	ASSERT_EQ (function.region, function1->region);
}

TEST (llvmc_analyzer, entry_function)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::unit unit1;
    function.results.push_back (&unit1);
    function.branch_ends.push_back (function.results.size ());
    mu::llvmc::ast::entry entry1;
    entry1.function = &function;
    mu::llvmc::ast::element element1 (&entry1, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (1, function1->results.size ());
	ASSERT_EQ (function.region, function1->region);
	ASSERT_EQ (function1, result.module->entry);
}

TEST (llvmc_analyzer, named_function)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
	ASSERT_EQ (function.region, function1->region);
}

TEST (llvmc_analyzer, not_global_error)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
	mu::llvmc::ast::unit_type type1;
    mu::llvmc::ast::parameter parameter (U"p0", &type1);
    parameter.region = mu::core::region (2, 2, 2, 3, 3, 3);
    mu::llvmc::ast::element element1 (&parameter, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
	ASSERT_EQ (parameter.region, result.error->region ());
}

TEST (llvmc_analyzer, module_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
	mu::llvmc::ast::unit_type type1;
    mu::llvmc::ast::element element1 (&type1, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
}

TEST (llvmc_analyzer, single_parameter)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 5, 5, 5);
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    parameter1.region = mu::core::region (3, 3, 3, 4, 4, 4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (function.region, function1->region);
    auto parameter2 (dynamic_cast <mu::llvmc::skeleton::parameter *> (function1->parameters [0]));
    auto type3 (dynamic_cast <mu::llvmc::skeleton::unit_type *> (parameter2->type ()));
    EXPECT_EQ (&type1, type3);
    EXPECT_EQ (0, function1->results.size ());
    ASSERT_EQ (parameter1.region, parameter2->region);
}

TEST (llvmc_analyzer, one_result_parameter)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 5, 5, 5);
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    parameter1.region = mu::core::region (3, 3, 3, 4, 4, 4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&type2, &parameter1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (function.region, function1->region);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (function1->parameters [0]);
    ASSERT_EQ (parameter1.region, parameter2->region);
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->branch_size (0));
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [0]));
    ASSERT_NE (nullptr, result2);
    auto result3 (dynamic_cast <mu::llvmc::skeleton::value *> (result2->value));
    ASSERT_NE (nullptr, result3);
    ASSERT_EQ (parameter2, result3);
    ASSERT_EQ (function1->entry, result2->value->branch);
}

TEST (llvmc_analyzer, two_result_parameter)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&type2, &parameter1);
    function.results.push_back (&result1);
    mu::llvmc::ast::result result2 (&type2, &parameter1);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (function1->parameters [0]);
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (2, function1->branch_ends [0]);
    ASSERT_EQ (2, function1->branch_size (0));
    auto result3 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [0]));
    ASSERT_NE (nullptr, result3);
    auto result4 (dynamic_cast <mu::llvmc::skeleton::value *> (result3->value));
    ASSERT_NE (nullptr, result4);
    ASSERT_EQ (parameter2, result4);
    ASSERT_EQ (function1->entry, result3->value->branch);
    auto result5 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [1]));
    ASSERT_NE (nullptr, result5);
    auto result6 (dynamic_cast <mu::llvmc::skeleton::value *> (result5->value));
    ASSERT_NE (nullptr, result6);
    ASSERT_EQ (parameter2, result6);
    ASSERT_EQ (function1->entry, result5->value->branch);
}

TEST (llvmc_analyzer, error_wrong_result_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 5, 5, 5);
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    parameter1.region = mu::core::region (3, 3, 3, 4, 4, 4);
    function.parameters.push_back (&parameter1);
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type3;
	type3.bits = &bits1;
    mu::llvmc::ast::result result1 (&type3, &parameter1);
    result1.region = mu::core::region (9, 9, 9, 10, 10, 10);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::actual_formal_result_type_mismatch, result.error->type ());
    ASSERT_EQ (parameter1.region, result.error->region ());
}

TEST (llvmc_analyzer, error_indistinct_result_branches1)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&type2, &parameter1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type2, &parameter1);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, error_indistinct_result_branches2)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    mu::llvmc::ast::unit_type value2;
    mu::llvmc::ast::result result1 (&value2, &element1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&value2, &parameter1);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element3 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element3);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::branch_analyzer_ancestor_exists, result.error->type ());
}

TEST (llvmc_analyzer, error_expression_cycle)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::expression expression1;
    expression1.arguments.push_back (&expression1);
    mu::llvmc::ast::result result1 (&type2, &expression1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::cycle_in_expressions, result.error->type ());
}

TEST (llvmc_analyzer, if_instruction)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 12, 12, 12);
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::skeleton::integer_type type3 (1);
    mu::llvmc::ast::value type4 (&type3);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type4);
    parameter1.region = mu::core::region (3, 3, 3, 4, 4, 4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker if_marker (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value if_ast (&if_marker);
    mu::llvmc::ast::expression expression1 ({&if_ast, &parameter1}, {});
    expression1.region = mu::core::region (10, 10, 10, 11, 11, 11);
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    element1.region = mu::core::region (6, 6, 6, 7, 7, 7);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    element2.region = mu::core::region (8, 8, 8, 9, 9, 9);
    mu::llvmc::ast::result result1 (&type2, &element1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type2, &element2);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element5 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element5);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (function1->parameters [0]);
    ASSERT_EQ (2, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (2, function1->branch_ends [1]);
    ASSERT_EQ (1, function1->branch_size (0));
    auto result3 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [0]));
    ASSERT_NE (nullptr, result3);
    auto named1 (dynamic_cast <mu::llvmc::skeleton::named *> (result3->value));
    ASSERT_NE (nullptr, named1);
    ASSERT_EQ (named1->region, element1.region);
    auto element3 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (named1->value_m));
    ASSERT_NE (nullptr, element3);
    ASSERT_EQ (1, function1->branch_size (1));
    auto result4 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [1]));
    ASSERT_NE (nullptr, result4);
    auto named2 (dynamic_cast <mu::llvmc::skeleton::named *> (result4->value));
    ASSERT_NE (nullptr, named2);
    ASSERT_EQ (named2->region, element2.region);
    auto element4 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (named2->value_m));
    ASSERT_EQ (element3->source, element4->source);
    ASSERT_EQ (4, element3->source->arguments.size ());
    ASSERT_EQ (parameter2, element3->source->arguments [1]);
    ASSERT_NE (element3->branch, element4->branch);
    ASSERT_NE (parameter2->branch, element3->branch);
    ASSERT_NE (parameter2->branch, element4->branch);
    ASSERT_EQ (parameter2->branch, element3->branch->parent);
    ASSERT_EQ (parameter2->branch, element4->branch->parent);
}

TEST (llvmc_analyzer, branches)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::skeleton::integer_type type3 (1);
    mu::llvmc::ast::value type4 (&type3);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::parameter parameter2 (U"p1", &type4);
    function.parameters.push_back (&parameter2);
    mu::llvmc::ast::parameter parameter3 (U"p2", &type4);
    function.parameters.push_back (&parameter3);
    mu::llvmc::skeleton::marker if_marker (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value if_ast (&if_marker);
    mu::llvmc::ast::expression expression1 ({&if_ast, &parameter1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    mu::llvmc::skeleton::marker add_marker (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value marker1 (&add_marker);
    mu::llvmc::ast::expression expression2 ({&marker1, &parameter2, &parameter2}, {&element1});
    mu::llvmc::ast::expression expression3 ({&marker1, &parameter3, &parameter3}, {&element2});
    mu::llvmc::ast::result result1 (&type4, &expression2);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type4, &expression3);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element7 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element7);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (3, function1->parameters.size ());
    auto parameter4 (function1->parameters [0]);
    auto parameter5 (function1->parameters [1]);
    auto parameter6 (function1->parameters [2]);
    ASSERT_EQ (2, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (2, function1->branch_ends [1]);
    ASSERT_EQ (1, function1->branch_size (0));
    auto result3 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [0]));
    ASSERT_NE (nullptr, result3);
    auto element3 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result3->value));
    ASSERT_NE (nullptr, element3);
    ASSERT_EQ (mu::llvmc::instruction_type::add, element3->marker ());
    ASSERT_EQ (4, element3->arguments.size ());
    ASSERT_EQ (&add_marker, element3->arguments [0]);
    ASSERT_EQ (parameter5, element3->arguments [1]);
    ASSERT_EQ (parameter5, element3->arguments [2]);
    ASSERT_EQ (1, function1->branch_size (1));
    auto result4 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [1]));
    ASSERT_NE (nullptr, result4);
    auto element4 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result4->value));
    ASSERT_NE (nullptr, element4);
    ASSERT_EQ (mu::llvmc::instruction_type::add, element4->marker ());
    ASSERT_EQ (4, element4->arguments.size ());
    ASSERT_EQ (&add_marker, element4->arguments [0]);
    ASSERT_EQ (parameter6, element4->arguments [1]);
    ASSERT_EQ (parameter6, element4->arguments [2]);
    ASSERT_NE (element3->branch, element4->branch);
    auto named1 (dynamic_cast <mu::llvmc::skeleton::named *> (element3->arguments [3]));
    ASSERT_NE (nullptr, named1);
    auto element5 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (named1->value_m));
    ASSERT_NE (nullptr, element5);
    auto named2 (dynamic_cast <mu::llvmc::skeleton::named *> (element4->arguments [3]));
    ASSERT_NE (nullptr, named2);
    auto element6 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (named2->value_m));
    ASSERT_NE (nullptr, element6);
    ASSERT_NE (element5, element6);
    ASSERT_EQ (element5->source, element6->source);
    auto instruction1 (element5->source);
    ASSERT_EQ (parameter4, instruction1->arguments [1]);
}

TEST (llvmc_analyzer, error_short_join)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (8);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::join join1;
    auto & branch1 (join1.add_branch ());
    branch1.arguments.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&value1, &join1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (mu::core::error_type::must_be_joining_at_least_two_branches, result.error->type ());
}

TEST (llvmc_analyzer, error_join_different_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (8);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::integer_type type2 (1);
    mu::llvmc::ast::value value2 (&type2);
    mu::llvmc::ast::parameter parameter2 (U"p1", &value2);
    function.parameters.push_back (&parameter2);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value4 (&marker1);
    mu::llvmc::ast::expression expression2 ({&value4, &parameter2}, {});
    mu::llvmc::ast::element element1 (&expression2, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression2, 1, 2, U"element2", empty_region);
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value value5 (&marker2);
    mu::llvmc::ast::expression expression3 ({&value5, &parameter1, &parameter1}, {&element2});
    mu::llvmc::ast::expression expression4 ({&value5, &parameter2, &parameter2}, {&element1});
    mu::llvmc::ast::join join1;
    auto & branch1 (join1.add_branch ());
    branch1.arguments.push_back (&expression3);
    auto & branch2 (join1.add_branch ());
    branch2.arguments.push_back (&expression4);
    
    mu::llvmc::ast::result result1 (&value1, &join1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element3 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element3);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (mu::core::error_type::joining_types_are_different, result.error->type ());
}

TEST (llvmc_analyzer, error_same_branch)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function.parameters.push_back (&parameter1);
    
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value2 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value2, &parameter1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);

    mu::llvmc::ast::expression expression2 ({&value2, &parameter1}, {&element1});
    mu::llvmc::ast::element element3 (&expression2, 0, 2, U"element3", empty_region);
    mu::llvmc::ast::element element4 (&expression2, 1, 2, U"element4", empty_region);
    
    mu::llvmc::ast::join join1;
    auto & branch1 (join1.add_branch ());
    branch1.arguments.push_back (&element1);
    auto & branch2 (join1.add_branch ());
    branch2.arguments.push_back (&element3);
    
    mu::llvmc::skeleton::unit_type type2;
    mu::llvmc::ast::value value4 (&type2);
    
    mu::llvmc::ast::result result1 (&value4, &join1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::result result2 (&value4, &element4);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::element element5 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element5);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (mu::core::error_type::branch_analyzer_intersection_exists, result.error->type ());
}

TEST (llvmc_analyzer, error_same_branch2)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function.parameters.push_back (&parameter1);
    
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value2 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value2, &parameter1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    
    mu::llvmc::ast::expression expression2 ({&value2, &parameter1}, {&element1});
    mu::llvmc::ast::element element3 (&expression2, 0, 2, U"element3", empty_region);
    mu::llvmc::ast::element element4 (&expression2, 1, 2, U"element4", empty_region);
    
    mu::llvmc::ast::join join1;
    auto & branch1 (join1.add_branch ());
    branch1.arguments.push_back (&element3);
    auto & branch2 (join1.add_branch ());
    branch2.arguments.push_back (&element1);
    
    mu::llvmc::skeleton::unit_type type2;
    mu::llvmc::ast::value value4 (&type2);
    
    mu::llvmc::ast::result result1 (&value4, &join1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::result result2 (&value4, &element2);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::result result3 (&value4, &join1);
    function.results.push_back (&result3);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::element element5 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element5);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (mu::core::error_type::branch_analyzer_ancestor_exists, result.error->type ());
}

TEST (llvmc_analyzer, join_simple)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function.parameters.push_back (&parameter1);
    
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value2 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value2, &parameter1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    
    mu::llvmc::ast::join join1;
    auto & branch1 (join1.add_branch ());
    branch1.arguments.push_back (&element1);
    auto & branch2 (join1.add_branch ());
    branch2.arguments.push_back (&element2);
    
    mu::llvmc::ast::unit_type type2;
    mu::llvmc::ast::result result3 (&type2, &join1);
    function.results.push_back (&result3);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::element element4 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element4);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size ());
    ASSERT_EQ (1, function2->branch_ends.size ());
    ASSERT_EQ (1, function2->branch_ends [0]);
    ASSERT_EQ (1, function2->predicate_offsets.size ());
    ASSERT_EQ (1, function2->predicate_offsets [0]);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
    ASSERT_NE (nullptr, result2);
    auto element3 (dynamic_cast <mu::llvmc::skeleton::join_element *> (result2->value));
    ASSERT_NE (nullptr, element3);
    ASSERT_EQ (1, element3->source->elements.size ());
    ASSERT_EQ (element3, element3->source->elements [0]);
}

TEST (llvmc_analyzer, disjoint_results)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value2 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value2, &parameter1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value value3 (&marker2);
    mu::llvmc::ast::expression expression2 ({&value3, &parameter1, &parameter1}, {&element1});
    mu::llvmc::ast::expression expression3 ({&value3, &parameter1, &parameter1}, {&element2});
    mu::llvmc::ast::result result1 (&value1, &expression2);
    function.results.push_back (&result1);
    mu::llvmc::ast::result result2 (&value1, &expression3);
    function.results.push_back (&result2);
    
    function.predicate_offsets.push_back (function.results.size ());
    function.branch_ends.push_back (function.results.size ());
    mu::llvmc::ast::element element3 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element3);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::branch_analyzer_disjoint, result.error->type ());
}

TEST (llvmc_analyzer, empty_call)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::ast::unit_type value1;
    mu::llvmc::ast::unit unit1;
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element3 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element3);
    mu::llvmc::ast::function function2;
    mu::llvmc::ast::expression expression1 ({&function1}, {});
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&expression1);
    function2.branch_ends.push_back (function2.results.size ());
    mu::llvmc::ast::element element2 (&function2, 0, 1, U"1", mu::empty_region);
    module1.globals.push_back (&element2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (2, result.module->globals.size ());
    auto function3 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_EQ (0, function3->parameters.size ());
    ASSERT_EQ (1, function3->results.size ());
    ASSERT_EQ (1, function3->branch_ends.size ());
    ASSERT_EQ (1, function3->branch_ends [0]);
    ASSERT_EQ (1, function3->predicate_offsets.size ());
    ASSERT_EQ (0, function3->predicate_offsets [0]);
    auto function4 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [1]));
    ASSERT_EQ (0, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (0, function4->predicate_offsets [0]);
    auto element1 (dynamic_cast <mu::llvmc::skeleton::call_element *> (function4->results [0]));
    ASSERT_NE (nullptr, element1);
    ASSERT_EQ (1, element1->source->elements.size ());
    ASSERT_EQ (element1, element1->source->elements [0]);
}

TEST (llvmc_analyzer, call_no_return)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::ast::unit_type value1;
    mu::llvmc::ast::unit unit1;
    mu::llvmc::ast::element element3 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element3);
    mu::llvmc::ast::function function2;
    mu::llvmc::ast::expression expression1 ({&function1}, {});
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&expression1);
    function2.branch_ends.push_back (function2.results.size ());
    mu::llvmc::ast::element element2 (&function2, 0, 1, U"1", mu::empty_region);
    module1.globals.push_back (&element2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (2, result.module->globals.size ());
    auto function3 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_EQ (0, function3->parameters.size ());
    ASSERT_EQ (0, function3->results.size ());
    ASSERT_EQ (0, function3->branch_ends.size ());
    ASSERT_EQ (0, function3->predicate_offsets.size ());
    auto function4 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [1]));
    ASSERT_EQ (0, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (0, function4->predicate_offsets [0]);
    auto element1 (dynamic_cast <mu::llvmc::skeleton::call_element *> (function4->results [0]));
    ASSERT_NE (nullptr, element1);
    ASSERT_EQ (1, element1->source->elements.size ());
    ASSERT_EQ (element1, element1->source->elements [0]);
}

TEST (llvmc_analyzer, empty_call_predicate)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::ast::unit_type value1;
    mu::llvmc::ast::unit unit1;
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    mu::llvmc::ast::function function2;
    mu::llvmc::ast::function function3;
    function3.predicate_offsets.push_back (function3.results.size ());
    function3.results.push_back (&unit1);
    function3.branch_ends.push_back (function3.results.size ());
    mu::llvmc::ast::element element2 (&function3, 0, 1, U"2", mu::empty_region);
    module1.globals.push_back (&element2);
    mu::llvmc::ast::expression expression2 ({&function1}, {});
    mu::llvmc::ast::expression expression1 ({&function3}, {&expression2});
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&expression1);
    function2.branch_ends.push_back (function2.results.size ());
    mu::llvmc::ast::element element3 (&function2, 0, 1, U"1", mu::empty_region);
    module1.globals.push_back (&element3);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (3, result.module->globals.size ());
    auto function4 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_EQ (0, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (0, function4->predicate_offsets [0]);
    auto function5 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [1]));
    ASSERT_EQ (0, function5->parameters.size ());
    ASSERT_EQ (1, function5->results.size ());
    ASSERT_EQ (1, function5->branch_ends.size ());
    ASSERT_EQ (1, function5->branch_ends [0]);
    ASSERT_EQ (1, function5->predicate_offsets.size ());
    ASSERT_EQ (0, function5->predicate_offsets [0]);
    auto function6 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [2]));
    ASSERT_EQ (0, function6->parameters.size ());
    ASSERT_EQ (1, function6->results.size ());
    ASSERT_EQ (1, function6->branch_ends.size ());
    ASSERT_EQ (1, function6->branch_ends [0]);
    ASSERT_EQ (1, function6->predicate_offsets.size ());
    ASSERT_EQ (0, function6->predicate_offsets [0]);
}

TEST (llvmc_analyzer, call_1_argument)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&value1, &parameter1);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    mu::llvmc::ast::function function2;
    mu::llvmc::ast::parameter parameter2 (U"p0", &value1);
    function2.parameters.push_back (&parameter2);
    mu::llvmc::ast::expression expression1 ({&element1, &parameter2}, {});
    mu::llvmc::ast::result result2 (&value1, &expression1);
    function2.results.push_back (&result2);
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.branch_ends.push_back (function2.results.size ());
    mu::llvmc::ast::element element2 (&function2, 0, 1, U"1", mu::empty_region);
    module1.globals.push_back (&element2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (2, result.module->globals.size ());
    auto function3 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_EQ (1, function3->parameters.size ());
    ASSERT_EQ (1, function3->results.size ());
    ASSERT_EQ (1, function3->branch_ends.size ());
    ASSERT_EQ (1, function3->branch_ends [0]);
    ASSERT_EQ (1, function3->predicate_offsets.size ());
    ASSERT_EQ (1, function3->predicate_offsets [0]);
    auto function4 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [1]));
    ASSERT_EQ (1, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (1, function4->predicate_offsets [0]);
    auto result3 (dynamic_cast <mu::llvmc::skeleton::result *> (function4->results [0]));
    ASSERT_NE (nullptr, result3);
    auto expression2 (dynamic_cast <mu::llvmc::skeleton::call_element *> (result3->value));
    ASSERT_NE (nullptr, expression2);
    ASSERT_EQ (1, expression2->source->elements.size ());
    ASSERT_EQ (expression2, expression2->source->elements [0]);
    ASSERT_EQ (function4->entry, expression2->branch);
}

TEST (llvmc_analyzer, error_call_wrong_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&value1, &parameter1);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    mu::llvmc::ast::function function2;
    mu::llvmc::skeleton::integer_type type2 (8);
    mu::llvmc::ast::value value2 (&type2);
    mu::llvmc::ast::parameter parameter2 (U"p0", &value2);
    parameter2.region = mu::core::region (8, 8, 8, 9, 9, 9);
    function2.parameters.push_back (&parameter2);
    mu::llvmc::ast::expression expression1 ({&function1, &parameter2}, {});
    mu::llvmc::ast::result result2 (&value1, &expression1);
    function2.results.push_back (&result2);
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.branch_ends.push_back (function2.results.size ());
    mu::llvmc::ast::element element2 (&function2, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element2);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::argument_type_does_not_match_parameter_type, result.error->type ());
    ASSERT_EQ (parameter2.region, result.error->region ());
}

TEST (llvmc_analyzer, int_type1)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (function2->parameters [0]->type ()));
    ASSERT_NE (nullptr, type2);
    ASSERT_EQ (1, type2->bits);
}

TEST (llvmc_analyzer, int_type1024)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1024");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (function2->parameters [0]->type ()));
    ASSERT_NE (nullptr, type2);
    ASSERT_EQ (1024, type2->bits);
}

TEST (llvmc_analyzer, fail_int_type2000000000)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"2000000000");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, ptr_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1024");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    auto type3 (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (function2->parameters [0]->type ()));
    ASSERT_NE (nullptr, type3);
    auto type4 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type3->pointed_type));
    ASSERT_EQ (1024, type4->bits);
}

TEST (llvmc_analyzer, instruction_add)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_alloca)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::alloca);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &type1}, {});
    mu::llvmc::ast::pointer_type type3 (&type1);
    mu::llvmc::ast::result result1 (&type3, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (2, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (instruction1->arguments [1]));
	ASSERT_NE (nullptr, type2);
	ASSERT_EQ (1, type2->bits);
}

TEST (llvmc_analyzer, instruction_and)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::and_i);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_ashr)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::ashr);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, DISABLED_instruction_atomicrmw)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::ashr);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_bitcast)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"32");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::bitcast);
    mu::llvmc::ast::value value1 (&marker1);
	mu::llvmc::ast::number bits2 (U"8");
    mu::llvmc::ast::integer_type type3;
	type3.bits = &bits2;
    mu::llvmc::ast::pointer_type type4 (&type3);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &type4}, {});
    mu::llvmc::ast::result result1 (&type4, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
    auto type5 (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (instruction1->arguments [2]));
    ASSERT_NE (nullptr, type5);
    auto type6 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type5->pointed_type));
    ASSERT_NE (nullptr, type6);
    ASSERT_EQ (8, type6->bits);
    ASSERT_EQ (*type5, *result2->type);
}

TEST (llvmc_analyzer, bitcast_error)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"32");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::bitcast);
    mu::llvmc::ast::value value1 (&marker1);
	mu::llvmc::ast::number bits2 (U"8");
    mu::llvmc::ast::integer_type type3;
	type3.bits = &bits2;
    mu::llvmc::ast::pointer_type type4 (&type3);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &type4}, {});
    expression1.region = mu::core::region (7, 7, 7, 8, 8, 8);
    mu::llvmc::ast::result result1 (&type4, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::region (7, 7, 7, 8, 8, 8), result.error->region ());
}

TEST (llvmc_analyzer, DISABLED_instruction_call)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::ashr);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_cmpxchg)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
	mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::parameter parameter2 (U"p1", &type2);
    function1.parameters.push_back (&parameter2);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::cmpxchg);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter2, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (2, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (4, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [1], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [3]);
}

TEST (llvmc_analyzer, DISABLED_instruction_extractelement)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::ashr);
    mu::llvmc::ast::value value1 (&marker1);
    expression1.arguments.push_back (&value1);
    expression1.arguments.push_back (&parameter1);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, DISABLED_instruction_extractvalue)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::extractvalue);
    mu::llvmc::ast::value value1 (&marker1);
    expression1.arguments.push_back (&value1);
    expression1.arguments.push_back (&parameter1);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_insertvalue)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
	mu::llvmc::ast::struct_type type2;
	type2.elements.push_back (&type1);
    mu::llvmc::ast::parameter parameter2 (U"p1", &type2);
    function1.parameters.push_back (&parameter2);
	mu::llvmc::ast::number number1 (U"0");
	mu::llvmc::ast::number bits2 (U"32");
	mu::llvmc::ast::integer_type type3;
	type3.bits = &bits2;
	mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type3, &number1}, {});
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::insertvalue);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter2, &parameter1, &expression2}, {});
    mu::llvmc::ast::result result1 (&type2, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (2, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (4, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [1], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
	auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (instruction1->arguments [3]));
	ASSERT_NE (nullptr, constant2);
}

TEST (llvmc_analyzer, instruction_extractvalue)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
	mu::llvmc::ast::struct_type type2;
	type2.elements.push_back (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
	mu::llvmc::ast::number number1 (U"0");
	mu::llvmc::ast::number bits2 (U"32");
	mu::llvmc::ast::integer_type type3;
	type3.bits = &bits2;
	mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type3, &number1}, {});
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::extractvalue);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &expression2}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (instruction1->arguments [2]));
	ASSERT_NE (nullptr, constant2);
}

TEST (llvmc_analyzer, extractvalue_range_error)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
	mu::llvmc::ast::struct_type type2;
	type2.elements.push_back (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
	mu::llvmc::ast::number number1 (U"1");
	mu::llvmc::ast::number bits2 (U"32");
	mu::llvmc::ast::integer_type type3;
	type3.bits = &bits2;
	mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type3, &number1}, {});
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::extractvalue);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &expression2}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, instruction_getelementptr)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
	mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::getelementptr);
    mu::llvmc::ast::value value1 (&marker1);
	mu::llvmc::ast::number number1 (U"0");
	mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number1}, {});
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &expression2}, {});
    mu::llvmc::ast::result result1 (&type2, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	auto index (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (instruction1->arguments [2]));
	ASSERT_NE (nullptr, index);
	ASSERT_EQ (0, index->value_m);
}

TEST (llvm_analyzer, error_non_result)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
	mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    function1.predicate_offsets.push_back (function1.results.size ());
	function1.results.push_back (&type1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
	ASSERT_EQ (mu::core::error_type::expecting_a_value, result.error->type ());
}

TEST (llvm_analyzer, error_non_expression)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number number1 (U"0");
	function1.results.push_back (&number1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
	ASSERT_EQ (mu::core::error_type::expecting_a_result, result.error->type ());
}

TEST (llvmc_analyzer, instruction_load)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::load);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
}

TEST (llvmc_analyzer, instruction_lshr)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::lshr);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_mul)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::mul);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_or)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::or_i);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_ptrtoint)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::ptrtoint);
    mu::llvmc::ast::value value1 (&marker1);
	mu::llvmc::ast::number bits2 (U"64");
    mu::llvmc::ast::integer_type type3;
	type3.bits = &bits2;
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &type3}, {});
    mu::llvmc::ast::result result1 (&type3, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
    auto type4 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (instruction1->arguments [2]));
    ASSERT_NE (nullptr, type4);
    ASSERT_EQ (*type4, *result2->type);
}

TEST (llvmc_analyzer, instruction_ptrfromint)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"64");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::inttoptr);
    mu::llvmc::ast::value value1 (&marker1);
	mu::llvmc::ast::number bits2 (U"8");
    mu::llvmc::ast::integer_type type2;
	type2.bits = &bits2;
    mu::llvmc::ast::pointer_type type3 (&type2);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &type3}, {});
    mu::llvmc::ast::result result1 (&type3, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
    auto type4 (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (instruction1->arguments [2]));
    ASSERT_NE (nullptr, type4);
    ASSERT_EQ (*type4, *result2->type);
}

TEST (llvmc_analyzer, instruction_sdiv)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::sdiv);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_select)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::select);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (4, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
    auto type2 (instruction1->type ());
}

TEST (llvmc_analyzer, instruction_shl)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::shl);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_srem)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::srem);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_store)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter2 (U"p1", &type2);
    function1.parameters.push_back (&parameter2);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::store);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter2}, {});
    mu::llvmc::ast::unit_type value2;
    mu::llvmc::ast::result result1 (&value2, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (2, function2->parameters.size ());
}

TEST (llvmc_analyzer, instruction_switch)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::switch_i);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::number number1 (U"0");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number1}, {});
    mu::llvmc::ast::number number2 (U"1");
	mu::llvmc::ast::expression expression3 ({&constant1, &type1, &number2}, {});
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &expression2, &expression3}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    mu::llvmc::ast::unit_type value2;
    mu::llvmc::ast::result result1 (&value2, &element1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::result result2 (&value2, &element2);
    function1.results.push_back (&result2);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element3 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element3);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
}

TEST (llvmc_analyzer, instruction_sub)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::sub);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, fail_instruction_sub_not_number)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::sub);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::number number1 (U"42,");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::number bits2 (U"32");
	mu::llvmc::ast::integer_type type2;
	type2.bits = &bits2;
	mu::llvmc::ast::expression expression2 ({&constant1, &type2, &number1}, {});
    mu::llvmc::ast::expression expression1 ({&value1, &expression2, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::error_converting_string_to_number, result.error->type ());
}

TEST (llvmc_analyzer, number_number)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"32");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::sub);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::number number1 (U"42");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number1}, {});
    mu::llvmc::ast::expression expression1 ({&value1, &expression2, &expression2}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (instruction1->arguments [1]));
	ASSERT_NE (nullptr, constant2);
	ASSERT_EQ (42, constant2->value_m);
}

TEST (llvmc_analyzer, number_dec)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"32");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::sub);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::number number1 (U"d42");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number1}, {});
    mu::llvmc::ast::expression expression1 ({&value1, &expression2, &expression2}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (instruction1->arguments [1]));
	ASSERT_NE (nullptr, constant2);
	ASSERT_EQ (42, constant2->value_m);
}

TEST (llvmc_analyzer, number_hex)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"32");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::sub);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::number number1 (U"h42");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number1}, {});
    mu::llvmc::ast::expression expression1 ({&value1, &expression2, &expression2}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (instruction1->arguments [1]));
	ASSERT_NE (nullptr, constant2);
	ASSERT_EQ (0x42, constant2->value_m);
}

TEST (llvmc_analyzer, number_oct)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"32");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::sub);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::number number1 (U"o42");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number1}, {});
    mu::llvmc::ast::expression expression1 ({&value1, &expression2, &expression2}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (instruction1->arguments [1]));
	ASSERT_NE (nullptr, constant2);
	ASSERT_EQ (042, constant2->value_m);
}

TEST (llvmc_analyzer, instruction_udiv)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::udiv);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_urem)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::urem);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, instruction_xor)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::xor_i);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter1}, {});
    mu::llvmc::ast::result result1 (&type1, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	auto instruction1 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
	ASSERT_NE (nullptr, instruction1);
	ASSERT_EQ (3, instruction1->arguments.size ());
	ASSERT_EQ (&marker1, instruction1->arguments [0]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [1]);
	ASSERT_EQ (function2->parameters [0], instruction1->arguments [2]);
}

TEST (llvmc_analyzer, constant_int)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::number number1 (U"42");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::number bits1 (U"32");
	mu::llvmc::ast::integer_type type2;
	type2.bits = &bits1;
	mu::llvmc::ast::expression expression1 ({&constant1, &type2, &number1}, {});
    function1.results.push_back (&expression1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->predicate_offsets.size ());
    ASSERT_EQ (0, function2->predicate_offsets [0]);
    ASSERT_EQ (1, function2->branch_ends.size ());
    ASSERT_EQ (1, function2->branch_ends [0]);
    ASSERT_EQ (1, function2->results.size ());
    auto predicate1 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (function2->results [0]));
    ASSERT_NE (nullptr, predicate1);
    auto type1 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (predicate1->type ()));
    ASSERT_NE (nullptr, type1);
    ASSERT_EQ (32, type1->bits);
    ASSERT_EQ (42, predicate1->value_m);
}

TEST (llvmc_analyzer, instruction_icmp_eq)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::icmp);
    mu::llvmc::ast::value value1 (&marker1);
	mu::llvmc::skeleton::predicate predicate1 (mu::llvmc::predicates::icmp_eq);
	mu::llvmc::ast::value value2 (&predicate1);
    mu::llvmc::ast::expression expression1 ({&value1, &value2, &parameter1, &parameter1}, {});
	mu::llvmc::ast::number bits2 (U"1");
    mu::llvmc::ast::integer_type type3;
	type3.bits = &bits2;
    mu::llvmc::ast::result result1 (&type3, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size ());
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
    ASSERT_NE (nullptr, result2);
    auto instruction (dynamic_cast <mu::llvmc::skeleton::icmp *> (result2->value));
    ASSERT_NE (nullptr, instruction);
    auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (instruction->type ()));
    ASSERT_NE (nullptr, type2);
    ASSERT_EQ (1, type2->bits);
}

TEST (llvmc_analyzer, multibranch_call)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::skeleton::integer_type type3 (1);
    mu::llvmc::ast::value type4 (&type3);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker if_marker (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value if_ast (&if_marker);
    mu::llvmc::ast::expression expression1 ({&if_ast, &parameter1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", empty_region);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", empty_region);
    mu::llvmc::ast::result result1 (&type2, &element1);
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type2, &element2);
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::element element5 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element5);
	
    mu::llvmc::ast::function function2;
    mu::llvmc::ast::parameter parameter2 (U"p0", &type4);
    function2.parameters.push_back (&parameter2);
    mu::llvmc::ast::expression expression2 ({&function, &parameter2}, {});
    mu::llvmc::ast::element element3 (&expression2, 0, 2, U"element3", empty_region);
    mu::llvmc::ast::element element4 (&expression2, 1, 2, U"element4", empty_region);
    mu::llvmc::ast::result result3 (&type2, &element3);
    function2.results.push_back (&result3);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    mu::llvmc::ast::result result4 (&type2, &element4);
    function2.results.push_back (&result4);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    mu::llvmc::ast::element element6 (&function2, 0, 1, U"1", mu::empty_region);
    module.globals.push_back (&element6);
	
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
}

TEST (llvmc_analyzer, loop_empty)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::ast::loop loop1;
    loop1.set_argument_offset ();
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&loop1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element2 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
	ASSERT_NE (nullptr, function2);
	ASSERT_EQ (1, function2->results.size ());
	auto element1 (dynamic_cast <mu::llvmc::skeleton::loop_element *> (function2->results [0]));
	ASSERT_NE (nullptr, element1);
    ASSERT_EQ (0, element1->source->argument_predicate_offset);
}

TEST (llvmc_analyzer, fail_loop_inner_error)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::ast::loop loop1;
    loop1.set_argument_offset ();
    mu::llvmc::ast::expression expression1 ({}, {});
    loop1.results.push_back (&expression1);
    loop1.add_predicate_offset ();
    loop1.add_branch_end ();
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&loop1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, fail_loop_same_branch)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::loop loop1;
    loop1.arguments.push_back (&parameter1);
    loop1.set_argument_offset ();
    mu::llvmc::ast::loop_parameter parameter2 (U"p1");
    loop1.parameters.push_back (&parameter2);
    loop1.results.push_back (&parameter2);
    loop1.add_predicate_offset ();
    loop1.add_branch_end ();
    loop1.results.push_back (&parameter2);
    loop1.add_predicate_offset ();
    loop1.add_branch_end ();
    mu::llvmc::ast::element element1 (&loop1, 0, 2, U"element1", empty_region);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&element1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element2 (&loop1, 1, 2, U"element2", empty_region);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&element2);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element3 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element3);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::branch_analyzer_leaves_exist, result.error->type ());
}

TEST (llvmc_analyzer, loop_passthrough)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &value1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::loop loop1;
    loop1.arguments.push_back (&parameter1);
    loop1.set_argument_offset ();
    mu::llvmc::ast::loop_parameter parameter2 (U"p1");
    loop1.parameters.push_back (&parameter2);
    loop1.add_predicate_offset ();
    loop1.add_branch_end ();
    loop1.results.push_back (&parameter2);
    loop1.add_predicate_offset ();
    loop1.add_branch_end ();
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&loop1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element2 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
	ASSERT_NE (nullptr, function2);
	ASSERT_EQ (1, function2->results.size ());
	auto element1 (dynamic_cast <mu::llvmc::skeleton::loop_element *> (function2->results [0]));
	ASSERT_NE (nullptr, element1);
    ASSERT_EQ (1, element1->source->argument_predicate_offset);
    ASSERT_EQ (1, element1->source->elements.size ());
    ASSERT_EQ (element1, element1->source->elements [0]);
}

TEST (llvmc_analyzer, branch_analyzer_single)
{
	mu::core::error * error (nullptr);
	mu::llvmc::skeleton::branch global (nullptr);
	mu::llvmc::branch_analyzer branches (&global, error);
	ASSERT_EQ (nullptr, error);
	auto most_specific1 (branches.add_branch (&global, mu::empty_region));
	ASSERT_EQ (nullptr, error);
    ASSERT_EQ (&global, most_specific1);
	auto most_specific2 (branches.add_branch (&global, mu::empty_region));
	ASSERT_EQ (nullptr, error);
    ASSERT_EQ (&global, most_specific2);
}

TEST (llvmc_analyzer, branch_analyzer_correct)
{
	mu::core::error * error (nullptr);
	mu::llvmc::skeleton::branch global (nullptr);
	mu::llvmc::branch_analyzer branches (&global, error);
	mu::llvmc::skeleton::branch branch1 (&global);
	mu::llvmc::skeleton::branch branch2 (&global);
	ASSERT_EQ (nullptr, error);
	auto most_specific1 (branches.add_branch (&branch1, mu::empty_region));
	ASSERT_EQ (nullptr, error);
    ASSERT_EQ (&branch1, most_specific1);
	branches.new_set ();
	ASSERT_EQ (nullptr, error);
	auto most_specific2 (branches.add_branch (&branch2, mu::empty_region));
	ASSERT_EQ (nullptr, error);
    ASSERT_EQ (&branch2, most_specific2);
	branches.new_set ();
	ASSERT_EQ (nullptr, error);
}

TEST (llvmc_analyzer, branch_analyzer_not_disjoint)
{
	mu::core::error * error (nullptr);
	mu::llvmc::skeleton::branch global (nullptr);
	mu::llvmc::branch_analyzer branches (&global, error);
	mu::llvmc::skeleton::branch branch1 (&global);
	ASSERT_EQ (nullptr, error);
	auto most_specific1 (branches.add_branch (&branch1, mu::empty_region));
	ASSERT_EQ (nullptr, error);
    ASSERT_EQ (&branch1, most_specific1);
	branches.new_set ();
	ASSERT_EQ (nullptr, error);
	auto most_specific2 (branches.add_branch (&branch1, mu::empty_region));
	ASSERT_EQ (nullptr, error);
    ASSERT_EQ (&branch1, most_specific2);
	branches.new_set ();
	ASSERT_NE (nullptr, error);
	ASSERT_EQ (mu::core::error_type::branch_analyzer_leaves_exist, branches.result->type ());
}

TEST (llvmc_analyzer, branch_analyzer_leaf_after_ancestor)
{
	mu::core::error * error (nullptr);
	mu::llvmc::skeleton::branch global (nullptr);
	mu::llvmc::branch_analyzer branches (&global, error);
	mu::llvmc::skeleton::branch branch1 (&global);
	mu::llvmc::skeleton::branch branch2 (&branch1);
	ASSERT_EQ (nullptr, error);
	branches.add_branch (&branch1, mu::empty_region);
	ASSERT_EQ (nullptr, error);
	branches.new_set ();
	ASSERT_EQ (nullptr, error);
	branches.add_branch (&branch2, mu::empty_region);
	ASSERT_EQ (nullptr, error);
	branches.new_set ();
	ASSERT_NE (nullptr, error);
	ASSERT_EQ (mu::core::error_type::branch_analyzer_intersection_exists, branches.result->type ());
}

TEST (llvmc_analyzer, branch_analyzer_ancestor_after_leaf)
{
	mu::core::error * error (nullptr);
	mu::llvmc::skeleton::branch global (nullptr);
	mu::llvmc::branch_analyzer branches (&global, error);
	mu::llvmc::skeleton::branch branch1 (&global);
	mu::llvmc::skeleton::branch branch2 (&branch1);
	ASSERT_EQ (nullptr, error);
	branches.add_branch (&branch2, mu::empty_region);
	ASSERT_EQ (nullptr, error);
	branches.new_set ();
	ASSERT_EQ (nullptr, error);
	branches.add_branch (&branch1, mu::empty_region);
	ASSERT_EQ (nullptr, error);
	branches.new_set ();
	ASSERT_NE (nullptr, error);
	ASSERT_EQ (mu::core::error_type::branch_analyzer_ancestor_exists, branches.result->type ());
}

TEST (llvmc_analyzer, branch_analyzer_disjoint)
{
	mu::core::error * error (nullptr);
	mu::llvmc::skeleton::branch global (nullptr);
	mu::llvmc::branch_analyzer branches (&global, error);
	mu::llvmc::skeleton::branch branch1 (&global);
	mu::llvmc::skeleton::branch branch2 (&global);
	ASSERT_EQ (nullptr, error);
	auto most_specific1 (branches.add_branch (&branch2, mu::core::region (1, 1, 1, 2, 2, 2)));
	ASSERT_EQ (nullptr, error);
    ASSERT_EQ (&branch2, most_specific1);
	auto most_specific2 (branches.add_branch (&branch1, mu::core::region (3, 3, 3, 4, 4, 4)));
	ASSERT_NE (nullptr, error);
    ASSERT_EQ (nullptr, most_specific2);
	ASSERT_EQ (mu::core::error_type::branch_analyzer_disjoint, branches.result->type ());
    ASSERT_EQ (mu::core::region (3, 3, 3, 4, 4, 4), error->region ());
}

TEST (llvmc_analyzer, asm1)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::asm_c asm1 (&value1, U"bswap $0", U"=r,r");
	mu::llvmc::ast::number number1 (U"0");
	mu::llvmc::ast::number bits1 (U"32");
	mu::llvmc::ast::integer_type type2;
	type2.bits = &bits1;
	mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type2, &number1}, {});
    mu::llvmc::ast::expression expression1 ({&asm1, &expression2}, {});
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&expression1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_EQ (1, function2->results.size ());
    auto asm2 (dynamic_cast <mu::llvmc::skeleton::inline_asm *> (function2->results [0]));
    ASSERT_NE (nullptr, asm2);
	ASSERT_EQ (2, asm2->arguments.size ());
	auto asm3 (dynamic_cast <mu::llvmc::skeleton::asm_c *> (asm2->arguments [0]));
	ASSERT_NE (nullptr, asm3);
    ASSERT_EQ (&type1, asm3->type_m);
	ASSERT_EQ (&type1, asm2->type ());
    ASSERT_EQ (U"bswap $0", asm3->text);
    ASSERT_EQ (U"=r,r", asm3->constraint);
	auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (asm2->arguments [1]));
	ASSERT_NE (nullptr, constant2);
}

TEST (llvmc_analyzer, fail_asm_not_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	function1.region = mu::core::region (1, 1, 1, 10, 10, 10);
	mu::llvmc::ast::number number1 (U"0");
	number1.region = mu::core::region (5, 5, 5, 6, 6, 6);
	mu::llvmc::ast::number bits1 (U"1");
	mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number1}, {});
	expression2.region = mu::core::region (4, 4, 4, 7, 7, 7);
    mu::llvmc::ast::asm_c asm1 (&expression2, U"text", U"constraint");
	asm1.region = mu::core::region (3, 3, 3, 8, 8, 8);
    mu::llvmc::ast::expression expression1 ({&asm1}, {});
	expression1.region = mu::core::region (2, 2, 2, 9, 9, 9);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&expression1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
	ASSERT_EQ (mu::core::error_type::expecting_a_type, result.error->type ());
	ASSERT_EQ (expression2.region, result.error->region ());
}

TEST (llvmc_analyzer, element_not_enough_fail)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	function1.region = mu::core::region (1, 1, 1, 2, 2, 2);
    mu::llvmc::ast::number number1 (U"1");
    number1.region = mu::core::region (3, 3, 3, 4, 4, 4);
	mu::llvmc::ast::number bits1 (U"1");
	mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression1 ({&constant1, &type1, &number1}, {});
    constant1.region = mu::core::region (5, 5, 5, 6, 6, 6);
    mu::llvmc::ast::element element1 (&expression1, 0, 2, U"element1", mu::core::region (11, 11, 11, 12, 12, 12));
    element1.region = mu::core::region (7, 7, 7, 8, 8, 8);
    mu::llvmc::ast::element element2 (&expression1, 1, 2, U"element2", mu::core::region (13, 13, 13, 14, 14, 14));
    element2.region = mu::core::region (9, 9, 9, 10, 10, 10);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&element1);
    function1.results.push_back (&element2);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element3 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element3);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (element2.region, result.error->region ());
}

/*  Function calls involving only global arguments will evaluate to having a global branch
    if branches are created off of this call e.g. an if instruction, the branches will have
    a global parent and will be incorrectly disjoint when subsequently combined with
    another argument that includes the function entry branch*/
TEST (llvmc_analyzer, global_argument_call_in_function_branch)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::number number1 (U"1");
	mu::llvmc::ast::number bits1 (U"1");
	mu::llvmc::ast::integer_type type2;
	type2.bits = &bits1;
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression3 ({&constant1, &type2, &number1}, {});
    mu::llvmc::ast::result result1 (&value1, &expression3);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    mu::llvmc::ast::function function2;
    mu::llvmc::ast::expression expression1 ({&function1}, {});
    mu::llvmc::ast::result result2 (&value1, &expression1);
    function2.results.push_back (&result2);
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.branch_ends.push_back (function2.results.size ());
    mu::llvmc::ast::element element2 (&function2, 0, 1, U"1", mu::empty_region);
    module1.globals.push_back (&element2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (2, result.module->globals.size ());
    auto function3 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_EQ (0, function3->parameters.size ());
    ASSERT_EQ (1, function3->results.size ());
    ASSERT_EQ (1, function3->branch_ends.size ());
    ASSERT_EQ (1, function3->branch_ends [0]);
    ASSERT_EQ (1, function3->predicate_offsets.size ());
    ASSERT_EQ (1, function3->predicate_offsets [0]);
    auto function4 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [1]));
    ASSERT_EQ (0, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (1, function4->predicate_offsets [0]);
    auto result3 (dynamic_cast <mu::llvmc::skeleton::result *> (function4->results [0]));
    ASSERT_NE (nullptr, result3);
    auto expression2 (dynamic_cast <mu::llvmc::skeleton::call_element *> (result3->value));
    ASSERT_NE (nullptr, expression2);
    ASSERT_EQ (function4->entry, expression2->branch);
}

TEST (llvmc_analyzer, fail_constant_array_bad_initializer)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::number number1 (U"4");
    mu::llvmc::ast::constant_int constant1;
    mu::llvmc::ast::constant_array constant2;
	mu::llvmc::ast::expression expression1 ({&type1}, {});
    constant2.type = &type1;
	constant2.initializer.push_back (&expression1);
    mu::llvmc::ast::fixed_array_type type2 (&type1, &number1);
    mu::llvmc::ast::result result1 (&type2, &constant2);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, array_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::number number1 (U"4");
    mu::llvmc::ast::fixed_array_type type2 (&type1, &number1);
    mu::llvmc::ast::parameter parameter1 (U"p0", &type2);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (1, function2->parameters.size ());
    auto type3 (dynamic_cast <mu::llvmc::skeleton::fixed_array_type *> (function2->parameters [0]->type ()));
    ASSERT_NE (nullptr, type3);
    ASSERT_EQ (4, type3->size);
    auto type4 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type3->element));
    ASSERT_NE (nullptr, type4);
    ASSERT_EQ (8, type4->bits);
}

TEST (llvmc_analyzer, constant_array)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::number number2 (U"ha5");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression1 ({&constant1, &type1, &number2}, {});
    mu::llvmc::ast::constant_array constant2;
    constant2.type = &type1;
    constant2.initializer.assign (4, &expression1);
    mu::llvmc::ast::number number1 (U"4");
    mu::llvmc::ast::fixed_array_type type2 (&type1, &number1);
    mu::llvmc::ast::result result1 (&type2, &constant2);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size ());
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
    ASSERT_NE (nullptr, result2);
    auto array_type (dynamic_cast <mu::llvmc::skeleton::fixed_array_type *> (result2->type));
    ASSERT_NE (nullptr, array_type);
    ASSERT_EQ (4, array_type->size);
    auto element_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (array_type->element));
    ASSERT_NE (nullptr, element_type);
    ASSERT_EQ (8, element_type->bits);
    auto constant_array (dynamic_cast <mu::llvmc::skeleton::constant_array *> (result2->value));
    ASSERT_NE (nullptr, constant_array);
    ASSERT_EQ (4, constant_array->initializer.size ());
    auto constant_int (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (constant_array->initializer [0]));
    ASSERT_NE (nullptr, constant_int);
    ASSERT_EQ (*element_type, *constant_int->type ());
    ASSERT_EQ (0xa5, constant_int->value_m);
}

TEST (llvmc_analyzer, DISABLED_typeof_single)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::number number2 (U"ha5");
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression2 ({&constant1, &type1, &number2}, {});
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::typeof_i);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1}, {});
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&expression1);
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size ());
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
    ASSERT_NE (nullptr, result2);
    auto array_type (dynamic_cast <mu::llvmc::skeleton::fixed_array_type *> (result2->type));
    ASSERT_NE (nullptr, array_type);
    ASSERT_EQ (4, array_type->size);
    auto element_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (array_type->element));
    ASSERT_NE (nullptr, element_type);
    ASSERT_EQ (8, element_type->bits);
    auto constant_array (dynamic_cast <mu::llvmc::skeleton::constant_array *> (result2->value));
    ASSERT_NE (nullptr, constant_array);
    ASSERT_EQ (4, constant_array->initializer.size ());
    auto constant_int (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (constant_array->initializer [0]));
    ASSERT_NE (nullptr, constant_int);
    ASSERT_EQ (*element_type, *constant_int->type ());
    ASSERT_EQ (0xa5, constant_int->value_m);
}

TEST (llvmc_analyzer, value_branch)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.predicate_offsets.push_back (function1.results.size ());
	mu::llvmc::skeleton::integer_type type2 (32);
    mu::llvmc::skeleton::constant_integer constant1 (mu::empty_region, &type2, 42);
    mu::llvmc::ast::value value1 (&constant1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.results.push_back (&value1);
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->predicate_offsets.size ());
    ASSERT_EQ (0, function2->predicate_offsets [0]);
    ASSERT_EQ (1, function2->branch_ends.size ());
    ASSERT_EQ (1, function2->branch_ends [0]);
    ASSERT_EQ (1, function2->results.size ());
    auto predicate1 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (function2->results [0]));
    ASSERT_NE (nullptr, predicate1);
    auto type1 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (predicate1->type ()));
    ASSERT_NE (nullptr, type1);
    ASSERT_EQ (&mu::llvmc::skeleton::branch::global, predicate1->branch);
    ASSERT_EQ (32, type1->bits);
    ASSERT_EQ (42, predicate1->value_m);
}

TEST (llvmc_analyzer, value_in_module)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
	mu::llvmc::skeleton::integer_type type1 (32);
    mu::llvmc::skeleton::constant_integer constant1 (mu::empty_region, &type1, 42);
    mu::llvmc::ast::value value1 (&constant1);
    module1.globals.push_back (&value1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
}

TEST (llvmc_analyzer, global_constant_int)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::number number1 (U"42");
	mu::llvmc::ast::number bits1 (U"32");
	mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression1 ({&constant1, &type1, &number1}, {});
    mu::llvmc::ast::element element1 (&expression1, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (0, result.module->globals.size ());
}

TEST (llvmc_analyzer, store_type_error)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"1");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::parameter parameter1 (U"p0", &type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::parameter parameter2 (U"p1", &type1);
    function1.parameters.push_back (&parameter2);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::store);
    mu::llvmc::ast::value value1 (&marker1);
    mu::llvmc::ast::expression expression1 ({&value1, &parameter1, &parameter2}, {});
    expression1.region = mu::core::region (2, 2, 2, 3, 3, 3);
    mu::llvmc::ast::unit_type value2;
    mu::llvmc::ast::result result1 (&value2, &expression1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
	ASSERT_EQ (expression1.region, result.error->region ());
}

TEST (llvmc_analyzer, global_variable)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::number number1 (U"42");
	mu::llvmc::ast::number bits1 (U"32");
	mu::llvmc::ast::integer_type type4;
	type4.bits = &bits1;
    mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression1 ({&constant1, &type4, &number1}, {});
    mu::llvmc::ast::global_variable global1 (&expression1);
    mu::llvmc::ast::element element1 (&global1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto global2 (dynamic_cast <mu::llvmc::skeleton::global_variable *> (result.module->globals [0]));
    ASSERT_NE (nullptr, global2);
    auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (global2->initializer));
    ASSERT_NE (nullptr, constant2);
    auto type1 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (constant2->type ()));
    ASSERT_NE (nullptr, type1);
    ASSERT_EQ (32, type1->bits);
    ASSERT_EQ (42, constant2->value_m);
    auto type2 (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (global2->type ()));
    ASSERT_NE (nullptr, type2);
    auto type3 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type2->pointed_type));
    ASSERT_NE (nullptr, type3);
    ASSERT_EQ (type3, type1);
}

TEST (llvmc_analyzer, global_variable_initializer_fail)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::number number1 (U"42");
	mu::llvmc::ast::set set1;
	mu::core::region region2 (5, 5, 5, 6, 6, 6);
	set1.region = region2;
    mu::llvmc::ast::global_variable global1 (&set1);
	mu::core::region region1 (3, 3, 3, 4, 4, 4);
	global1.region = region1;
    mu::llvmc::ast::element element1 (&global1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
	ASSERT_EQ (mu::core::region (region1.first, region2.last), result.error->region ());
}

TEST (llvmc_analyzer, global_variable_initializer_error)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::number number1 (U"42");
	mu::core::region region2 (5, 5, 5, 6, 6, 6);
	number1.region = region2;
    mu::llvmc::ast::global_variable global1 (&number1);
	mu::core::region region1 (3, 3, 3, 4, 4, 4);
	global1.region = region1;
    mu::llvmc::ast::element element1 (&global1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
	ASSERT_EQ (region2, result.error->region ());
}

TEST (llvmc_analyzer, null_pointer)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::constant_pointer_null constant1;
    constant1.type = &type2;
    mu::llvmc::ast::result result1 (&type2, &constant1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->predicate_offsets.size ());
    ASSERT_EQ (1, function2->predicate_offsets [0]);
    ASSERT_EQ (1, function2->branch_ends.size ());
    ASSERT_EQ (1, function2->branch_ends [0]);
    ASSERT_EQ (1, function2->results.size ());
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
    ASSERT_NE (nullptr, result2);
    auto constant2 (dynamic_cast <mu::llvmc::skeleton::constant_pointer_null *> (result2->value));
    ASSERT_NE (nullptr, constant2);
    auto type3 (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (constant2->type ()));
    ASSERT_NE (nullptr, type3);
    auto type4 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type3->pointed_type));
    ASSERT_NE (nullptr, type4);
    ASSERT_EQ (&mu::llvmc::skeleton::branch::global, constant2->branch);
    ASSERT_EQ (8, type4->bits);
}

TEST (llvmc_analyzer, struct_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
    mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
    mu::llvmc::ast::struct_type type2;
	type2.elements.push_back (&type1);
	type2.names [U"name1"] = 0;
    mu::llvmc::ast::undefined undefined1;
    undefined1.type = &type2;
    mu::llvmc::ast::result result1 (&type2, &undefined1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.globals.push_back (&element1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function2);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->predicate_offsets.size ());
    ASSERT_EQ (1, function2->predicate_offsets [0]);
    ASSERT_EQ (1, function2->branch_ends.size ());
    ASSERT_EQ (1, function2->branch_ends [0]);
    ASSERT_EQ (1, function2->results.size ());
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
    ASSERT_NE (nullptr, result2);
    auto undefined2 (dynamic_cast <mu::llvmc::skeleton::undefined *> (result2->value));
    ASSERT_NE (nullptr, undefined2);
    auto type3 (dynamic_cast <mu::llvmc::skeleton::struct_type *> (undefined2->type ()));
    ASSERT_NE (nullptr, type3);
	ASSERT_EQ (1, type3->elements.size ());
	ASSERT_EQ (1, type3->names.size ());
	ASSERT_NE (type3->names.end (), type3->names.find (U"name1"));
	auto constant1 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (type3->names [U"name1"]));
	ASSERT_NE (nullptr, constant1);
	ASSERT_EQ (0, constant1->value_m);
    auto type4 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type3->elements [0]));
    ASSERT_NE (nullptr, type4);
    ASSERT_EQ (&mu::llvmc::skeleton::branch::global, undefined2->branch);
    ASSERT_EQ (8, type4->bits);
}

TEST (llvmc_analyzer, empty_template)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
    mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::template_c template_l (&context1);
	mu::llvmc::ast::template_parameter parameter1 (U"parameter1");
	parameter1.argument = 0;
	template_l.parameters.push_back (&parameter1);
	template_l.body.push_back (&parameter1);
	mu::llvmc::ast::expression expression1 ({&template_l, &function}, {});
	mu::llvmc::ast::element element1 (&expression1, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
	ASSERT_EQ (function.region, function1->region);
}

TEST (llvmc_analyzer, function_clone)
{
    mu::llvmc::template_context template1;
	mu::llvmc::ast::function function1 (&template1);
	function1.predicate_offsets.push_back (42);
	function1.region = mu::core::region (1, 1, 1, 2, 2, 2);
    mu::llvmc::clone_context context (&template1);
	auto function2 (dynamic_cast <mu::llvmc::ast::function *> (function1.clone (context)));
	ASSERT_NE (nullptr, function2);
	ASSERT_NE (&function1, function2);
	ASSERT_EQ (1, function2->predicate_offsets.size ());
	ASSERT_EQ (42, function2->predicate_offsets [0]);
	ASSERT_EQ (function1.region, function2->region);
}

TEST (llvmc_analyzer, template_c_clone)
{
    mu::llvmc::template_context template1 ({nullptr});
	mu::llvmc::template_context template3 ({&template1});
	mu::llvmc::ast::template_c template0 (&template1, &template3);
    mu::llvmc::clone_context context (&template1);
	auto template2 (dynamic_cast <mu::llvmc::ast::template_c *> (template0.clone (context)));
	ASSERT_NE (&template0, template2);
	ASSERT_NE (nullptr, template2);
	ASSERT_EQ (&template1, template2->base);
}

TEST (llvmc_analyzer, module_clone)
{
	mu::llvmc::template_context context2 ({nullptr});
	mu::llvmc::ast::module module1 (&context2);
	mu::llvmc::ast::unit unit1;
	module1.names [U"unit"] = &unit1;
	module1.region = mu::core::region (1, 1, 1, 2, 2, 2);
	mu::llvmc::clone_context context1 (&context2);
	auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.clone (context1)));
	ASSERT_NE (nullptr, module2);
	ASSERT_NE (&module1, module2);
	ASSERT_EQ (1, module2->names.size ());
	ASSERT_EQ (module1.region, module2->region);
}

TEST (llvmc_analyzer, function_parameter_clone)
{
	mu::llvmc::ast::function function1;
	mu::llvmc::ast::number bits1 (U"8");
	mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
	mu::llvmc::ast::parameter parameter1 (U"parameter1", &type1);
	function1.parameters.push_back (&parameter1);
	mu::llvmc::ast::result result1 (&type1, &parameter1);
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    mu::llvmc::template_context template1 ({nullptr});
    mu::llvmc::clone_context context (&template1);
	auto function2 (dynamic_cast <mu::llvmc::ast::function *> (function1.clone (context)));
	ASSERT_NE (nullptr, function2);
	ASSERT_EQ (1, function2->parameters.size ());
	ASSERT_EQ (1, function2->results.size ());
	auto result2 (dynamic_cast <mu::llvmc::ast::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result2);
	ASSERT_EQ (function2->parameters [0], result2->value);
}

TEST (llvmc_analyzer, function_template)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::template_c template_l (&context1);
	mu::llvmc::ast::template_parameter parameter1 (U"parameter1", &context1);
    mu::llvmc::ast::function function (&context1);
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
	mu::llvmc::ast::parameter parameter2 (&context1);
	parameter2.name = U"parameter2";
	parameter2.type = &parameter1;
	function.parameters.push_back (&parameter2);
	mu::llvmc::ast::result result1 (&parameter1, &parameter2, &context1);
	function.results.push_back (&result1);
	function.predicate_offsets.push_back (function.results.size ());
	function.branch_ends.push_back (function.results.size ());
	parameter1.argument = 0;
	template_l.parameters.push_back (&parameter1);
	template_l.body.push_back (&function);
	mu::llvmc::ast::number bits1 (U"8");
	mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
	mu::llvmc::ast::expression expression1 ({&template_l, &type1}, {});
	mu::llvmc::ast::element element1 (&expression1, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (1, function1->parameters.size ());
    EXPECT_EQ (1, function1->results.size ());
    auto type3 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (function1->parameters [0]->type ()));
    ASSERT_NE (nullptr, type3);
    ASSERT_EQ (8, type3->bits);
}

TEST (llvmc_analyzer, nested_template)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
		mu::llvmc::template_context context0 ({nullptr});
		mu::llvmc::ast::template_c template0 (&context0);
		mu::llvmc::ast::template_parameter parameter1 (U"parameter1", &context0);
		parameter1.argument = 0;
		template0.parameters.push_back (&parameter1);
			mu::llvmc::template_context context1 ({&context0});
			mu::llvmc::ast::template_c template1 (&context1, &context0);
			mu::llvmc::ast::function function (&context1);
			function.region = mu::core::region (2, 2, 2, 3, 3, 3);
			mu::llvmc::ast::parameter parameter2 (&context1);
			parameter2.name = U"parameter2";
			parameter2.type = &parameter1;
			function.parameters.push_back (&parameter2);
			mu::llvmc::ast::result result1 (&parameter1, &parameter2, &context1);
			function.results.push_back (&result1);
			function.predicate_offsets.push_back (function.results.size ());
			function.branch_ends.push_back (function.results.size ());
			template1.body.push_back (&function);
		mu::llvmc::ast::expression expression2 ({&template1}, {}, &context0);
		template0.body.push_back (&expression2);
	mu::llvmc::ast::number bits1 (U"8");
	mu::llvmc::ast::integer_type type1;
	type1.bits = &bits1;
	mu::llvmc::ast::expression expression1 ({&template0, &type1}, {});
	mu::llvmc::ast::element element1 (&expression1, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (1, function1->parameters.size ());
    EXPECT_EQ (1, function1->results.size ());
    auto type3 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (function1->parameters [0]->type ()));
    ASSERT_NE (nullptr, type3);
    ASSERT_EQ (8, type3->bits);
}

TEST (llvmc_analyzer, template_shared)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::template_c template_l (&context1);
    mu::llvmc::ast::function function (&context1);
    function.region = mu::core::region (2, 2, 2, 3, 3, 3);
	mu::llvmc::ast::number bits1 (U"16");
	mu::llvmc::ast::integer_type type2;
	type2.bits = &bits1;
	mu::llvmc::ast::number number1 (U"0");
	mu::llvmc::ast::constant_int constant1;
	mu::llvmc::ast::expression expression3 ({&constant1, &type2, &number1}, {});
	mu::llvmc::ast::result result1 (&type2, &expression3, &context1);
	function.results.push_back (&result1);
	function.predicate_offsets.push_back (function.results.size ());
	function.branch_ends.push_back (function.results.size ());
	template_l.body.push_back (&function);
	mu::llvmc::ast::expression expression1 ({&template_l}, {});
	mu::llvmc::ast::element element1 (&expression1, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
	mu::llvmc::ast::expression expression2 ({&template_l}, {});
	mu::llvmc::ast::element element2 (&expression2, 0, 1, U"1", mu::empty_region);
    module.globals.push_back (&element2);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
	ASSERT_EQ (2, result.module->globals.size ());
	auto function1 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
	ASSERT_NE (nullptr, function1);
	ASSERT_EQ (1, function1->results.size ());
	auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [0]));
	ASSERT_NE (nullptr, result2);
	auto value1 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (result2->value));
	ASSERT_NE (nullptr, value1);
	auto function2 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [1]));
	ASSERT_NE (nullptr, function2);
	ASSERT_EQ (1, function2->results.size ());
	auto result3 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
	ASSERT_NE (nullptr, result3);
	auto value2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (result3->value));
	ASSERT_NE (nullptr, value2);
	ASSERT_EQ (value1, value2);
}

TEST (llvmc_analyzer, template_naming)
{
	mu::llvmc::analyzer analyzer;
	mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::module module;
	mu::llvmc::ast::function function1 (&context1);
	mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region, &context1);
	mu::llvmc::ast::template_c template1 (&context1);
	template1.body.push_back (&element1);
	mu::llvmc::ast::expression expression1 ({&template1}, {});
	mu::llvmc::ast::element element2 (&expression1, 0, 1, U"1", mu::empty_region);
	module.globals.push_back (&element2);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
}

TEST (llvmc_analyzer, namespace_c_module)
{
	mu::llvmc::analyzer analyzer;
	mu::llvmc::ast::module module1;
	mu::llvmc::ast::function function1;
    mu::llvmc::ast::unit unit1;
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
	mu::llvmc::ast::element element1 (&function1, 0, 1, U"0", mu::empty_region);
    module1.names [U"0"] = &element1;
    module1.globals.push_back (&element1);
    mu::llvmc::ast::module module2;
    mu::llvmc::ast::namespace_c namespace1;
    namespace1.node_m = &module1;
    namespace1.member = U"0";
    mu::llvmc::ast::expression expression1 ({&namespace1}, {});
    mu::llvmc::ast::function function2;
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&expression1);
    function2.branch_ends.push_back (function2.results.size ());
    mu::llvmc::ast::element element2 (&function2, 0, 1, U"0", mu::empty_region);
    module2.names [U"0"] = &element2;
    module2.globals.push_back (&element2);
    auto result (analyzer.analyze (&module2));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->globals.size ());
    auto function3 (dynamic_cast <mu::llvmc::skeleton::function *> (result.module->globals [0]));
    ASSERT_NE (nullptr, function3);
    ASSERT_EQ (1, function3->results.size ());
    auto element3 (dynamic_cast <mu::llvmc::skeleton::call_element *> (function3->results [0]));
    ASSERT_NE (nullptr, element3);
    ASSERT_EQ (1, element3->source->arguments.size ());
    auto function4 (dynamic_cast <mu::llvmc::skeleton::function *> (element3->source->arguments [0]));
    ASSERT_NE (nullptr, function4);
    ASSERT_EQ (1, function4->results.size ());
	auto unit2 (dynamic_cast <mu::llvmc::skeleton::unit_value *> (function4->results [0]));
	ASSERT_NE (nullptr, unit2);
}

TEST (llvmc_analyzer, nested_module)
{
	mu::llvmc::analyzer analyzer;
	mu::llvmc::ast::module module1;
	mu::llvmc::ast::module module2;
	module1.globals.push_back (&module2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (0, result.module->globals.size ());
}

TEST (llvmc_analyzer, namespace_clone)
{
	mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::unit unit1 (&context1);
	mu::llvmc::ast::namespace_c namespace1 (U"name1", &unit1, &context1);
	mu::llvmc::clone_context context2 (&context1);
	auto namespace2 (dynamic_cast <mu::llvmc::ast::namespace_c *> (namespace1.clone (context2)));
	ASSERT_NE (nullptr, namespace2);
	ASSERT_NE (&namespace1, namespace2);
	auto unit2 (dynamic_cast <mu::llvmc::ast::unit *> (namespace2->node_m));
	ASSERT_NE (&unit1, unit2);
}

TEST (llvmc_analyzer, struct_clone)
{
	mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::unit_type unit1 (&context1);
	mu::llvmc::ast::struct_type struct1 (&context1);
	struct1.elements.push_back (&unit1);
	struct1.names [U"name1"] = 0;
	mu::llvmc::clone_context context2 (&context1);
	auto struct2 (dynamic_cast <mu::llvmc::ast::struct_type *> (struct1.clone (context2)));
	ASSERT_NE (nullptr, struct2);
	ASSERT_NE (&struct1, struct2);
	ASSERT_EQ (1, struct2->names.size ());
	ASSERT_NE (struct2->names.end (), struct2->names.find (U"name1"));
}

TEST (llvmc_analyzer, function_prototype_error_overwrite)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.region = mu::core::region (2, 2, 2, 5, 5, 5);
	mu::llvmc::ast::unit unit1;
    mu::llvmc::ast::expression expression1 ({&unit1}, {});
    mu::llvmc::ast::parameter parameter1 (U"p0", &expression1);
    parameter1.region = mu::core::region (3, 3, 3, 4, 4, 4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::element element1 (&function, 0, 1, U"0", mu::empty_region);
    module.globals.push_back (&element1);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
	auto error (result.error);
	ASSERT_EQ (mu::core::error_type::only_function_pointers_can_be_target_of_call, error->type ());
}

TEST (llvmc_analyzer, expression_clone)
{
	mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::expression expression1 (&context1);
	expression1.region = mu::core::region (1, 1, 1, 2, 2, 2);
	mu::llvmc::clone_context context2 (&context1);
	auto expression2 (dynamic_cast <mu::llvmc::ast::expression *> (expression1.clone (context2)));
	ASSERT_EQ (expression1.region, expression2->region);
}

TEST (llvmc_analyzer, element_clone)
{
	mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::node node1;
	mu::llvmc::ast::element element1 (&node1, 1, 2, U"thing", mu::core::region (1, 1, 1, 2, 2, 2), &context1);
	mu::llvmc::clone_context context2 (&context1);
	auto element2 (dynamic_cast <mu::llvmc::ast::element *> (element1.clone (context2)));
	ASSERT_EQ (element1.region, element2->region);
}

TEST (llvmc_analyzer, set_clone)
{
	mu::llvmc::template_context context1 ({nullptr});
	mu::llvmc::ast::node node1;
	mu::llvmc::ast::set set1 (&context1);
	set1.region = mu::core::region (1, 1, 1, 2, 2, 2);
	mu::llvmc::clone_context context2 (&context1);
	auto set2 (dynamic_cast <mu::llvmc::ast::set *> (set1.clone (context2)));
	ASSERT_EQ (set1.region, set2->region);
}