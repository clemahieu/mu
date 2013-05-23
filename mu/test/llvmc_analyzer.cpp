#include <gtest/gtest.h>

#include <mu/llvmc/analyzer.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/skeleton.hpp>
#include <mu/core/error.hpp>

TEST (llvmc_ast, iteration)
{
    mu::llvmc::ast::function function1;
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::result *, size_t)
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
    mu::llvmc::ast::function function1;
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::result result1 (&value1);
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::result *, size_t)
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
    mu::llvmc::ast::function function1;
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    mu::llvmc::ast::unit unit1;
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::result *, size_t)
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
    mu::llvmc::ast::function function1;
    size_t result_calls (0);
    size_t predicate_calls (0);
    size_t transition_calls (0);
    size_t branch_calls (0);
    size_t loop_calls (0);
    mu::llvmc::ast::unit unit1;
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.results.push_back (&unit1);
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.for_each_results (
                                [&]
                                (mu::llvmc::ast::result *, size_t)
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

TEST (llvmc_analyzer, empty)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (0, result.module->functions.size ());
}

TEST (llvmc_analyzer, fail_not_module)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::node node;
    auto result (analyzer.analyze (&node));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, empty_function)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.name = U"0";
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [U"0"]);
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
}

TEST (llvmc_analyzer, single_parameter)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.name = U"0";
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function.parameters.push_back (&parameter1);
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [U"0"]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (dynamic_cast <mu::llvmc::skeleton::unit_type *> (function1->parameters [0]->type ()));
    EXPECT_EQ (&type1, parameter2);
    EXPECT_EQ (0, function1->results.size ());
}

TEST (llvmc_analyzer, one_result_parameter)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.name = U"0";
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &parameter1;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [U"0"]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (function1->parameters [0]);
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
    function.name = U"0";
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &parameter1;
    function.results.push_back (&result1);
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &parameter1;
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [U"0"]);
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

TEST (llvmc_analyzer, error_indistinct_result_branches)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &parameter1;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &parameter1;
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, error_expression_cycle)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::definite_expression expression1;
    expression1.arguments.push_back (&expression1);
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &expression1;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
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
    function.name = U"0";
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::skeleton::integer_type type3 (1);
    mu::llvmc::ast::value type4 (&type3);
    mu::llvmc::ast::parameter parameter1 (&type4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker if_marker (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value if_ast (&if_marker);
    mu::llvmc::ast::definite_expression expression1;
    expression1.arguments.push_back (&if_ast);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &element1;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &element2;
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [U"0"]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (function1->parameters [0]);
    ASSERT_EQ (2, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (2, function1->branch_ends [1]);
    ASSERT_EQ (1, function1->branch_size (0));
    auto result3 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [0]));
    ASSERT_NE (nullptr, result3);
    auto element3 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (result3->value));
    ASSERT_NE (nullptr, element3);
    ASSERT_EQ (1, function1->branch_size (1));
    auto result4 (dynamic_cast <mu::llvmc::skeleton::result *> (function1->results [1]));
    ASSERT_NE (nullptr, result4);
    auto element4 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (result4->value));
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
    function.name = U"0";
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::skeleton::integer_type type3 (1);
    mu::llvmc::ast::value type4 (&type3);
    mu::llvmc::ast::parameter parameter1 (&type4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::parameter parameter2 (&type4);
    function.parameters.push_back (&parameter2);
    mu::llvmc::ast::parameter parameter3 (&type4);
    function.parameters.push_back (&parameter3);
    mu::llvmc::skeleton::marker if_marker (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value if_ast (&if_marker);
    mu::llvmc::ast::definite_expression expression1;
    expression1.arguments.push_back (&if_ast);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    mu::llvmc::skeleton::marker add_marker (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value add_ast (&add_marker);    
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&add_ast);
    expression2.arguments.push_back (&parameter2);
    expression2.arguments.push_back (&parameter2);
    expression2.set_predicate_position ();
    expression2.arguments.push_back (&element1);
    mu::llvmc::ast::definite_expression expression3;
    expression3.arguments.push_back (&add_ast);
    expression3.arguments.push_back (&parameter3);
    expression3.arguments.push_back (&parameter3);
    expression3.set_predicate_position ();
    expression3.arguments.push_back (&element2);
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &expression2;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &expression3;
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [U"0"]);
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
    auto element5 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (element3->arguments [3]));
    ASSERT_NE (nullptr, element5);
    auto element6 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (element4->arguments [3]));
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
    mu::llvmc::ast::parameter parameter1 (&value1);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::join join1;
    mu::llvmc::ast::value value2 (&join1);
    expression1.arguments.push_back (&value2);
    expression1.arguments.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&value1);
    result1.value = &expression1;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (mu::core::error_type::must_be_joining_at_least_two_values, result.error->type ());
}

TEST (llvmc_analyzer, error_join_different_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (8);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (&value1);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::integer_type type2 (1);
    mu::llvmc::ast::value value2 (&type2);
    mu::llvmc::ast::parameter parameter2 (&value2);
    function.parameters.push_back (&parameter2);
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value4 (&marker1);
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&value4);
    expression2.arguments.push_back (&parameter2);
    expression2.set_predicate_position ();
    mu::llvmc::ast::element element1 (&expression2, 0, 2);
    mu::llvmc::ast::element element2 (&expression2, 1, 2);
    mu::llvmc::ast::definite_expression expression3;
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value value5 (&marker2);
    expression3.arguments.push_back (&value5);
    expression3.arguments.push_back (&parameter1);
    expression3.arguments.push_back (&parameter1);
    expression3.set_predicate_position ();
    expression3.arguments.push_back (&element2);
    
    mu::llvmc::ast::definite_expression expression4;
    expression4.arguments.push_back (&value5);
    expression4.arguments.push_back (&parameter2);
    expression4.arguments.push_back (&parameter2);
    expression4.set_predicate_position ();
    expression4.arguments.push_back (&element1);
    
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::join join1;
    mu::llvmc::ast::value value3 (&join1);
    expression1.arguments.push_back (&value3);
    expression1.arguments.push_back (&expression3);
    expression1.arguments.push_back (&expression4);
    expression1.set_predicate_position ();
    
    mu::llvmc::ast::result result1 (&value1);
    result1.value = &expression1;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);
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
    mu::llvmc::ast::parameter parameter1 (&value1);
    function.parameters.push_back (&parameter1);
    
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value2 (&marker1);
    expression1.arguments.push_back (&value2);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&value2);
    expression2.arguments.push_back (&parameter1);
    expression2.set_predicate_position ();
    expression2.arguments.push_back (&element1);
    mu::llvmc::ast::element element3 (&expression2, 0, 2);
    mu::llvmc::ast::element element4 (&expression2, 1, 2);
    
    mu::llvmc::ast::definite_expression expression3;
    mu::llvmc::skeleton::join join1;
    mu::llvmc::ast::value value3 (&join1);
    expression3.arguments.push_back (&value3);
    expression3.arguments.push_back (&element1);
    expression3.arguments.push_back (&element3);
    expression3.set_predicate_position ();
    
    mu::llvmc::skeleton::unit_type type2;
    mu::llvmc::ast::value value4 (&type2);
    
    mu::llvmc::ast::result result1 (&value4);
    result1.value = &expression3;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::result result2 (&value4);
    result2.value = &element4;
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (mu::core::error_type::branches_are_not_disjoint, result.error->type ());
}

TEST (llvmc_analyzer, error_same_branch2)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (&value1);
    function.parameters.push_back (&parameter1);
    
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value2 (&marker1);
    expression1.arguments.push_back (&value2);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&value2);
    expression2.arguments.push_back (&parameter1);
    expression2.set_predicate_position ();
    expression2.arguments.push_back (&element1);
    mu::llvmc::ast::element element3 (&expression2, 0, 2);
    mu::llvmc::ast::element element4 (&expression2, 1, 2);
    
    mu::llvmc::ast::definite_expression expression3;
    mu::llvmc::skeleton::join join1;
    mu::llvmc::ast::value value3 (&join1);
    expression3.arguments.push_back (&value3);
    expression3.arguments.push_back (&element3); // Switched order from above
    expression3.arguments.push_back (&element1);
    
    mu::llvmc::skeleton::unit_type type2;
    mu::llvmc::ast::value value4 (&type2);
    
    mu::llvmc::ast::result result1 (&value4);
    result1.value = &expression3;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::result result2 (&value4);
    result2.value = &element2;
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    mu::llvmc::ast::result result3 (&value4);
    result3.value = &expression3;
    function.results.push_back (&result3);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (mu::core::error_type::branches_are_not_disjoint, result.error->type ());
}

TEST (llvmc_analyzer, disjoint_results)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.name = U"0";
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (&value1);
    function.parameters.push_back (&parameter1);
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value value2 (&marker1);
    expression1.arguments.push_back (&value2);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    mu::llvmc::skeleton::marker marker2 (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value value3 (&marker2);
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&value3);
    expression2.arguments.push_back (&parameter1);
    expression2.arguments.push_back (&parameter1);
    expression2.set_predicate_position ();
    expression2.arguments.push_back (&element1);
    mu::llvmc::ast::definite_expression expression3;
    expression3.arguments.push_back (&value3);
    expression3.arguments.push_back (&parameter1);
    expression3.arguments.push_back (&parameter1);
    expression3.set_predicate_position ();
    expression3.arguments.push_back (&element2);
    mu::llvmc::ast::result result1 (&value1);
    result1.value = &expression2;
    function.results.push_back (&result1);
    mu::llvmc::ast::result result2 (&value1);
    result2.value = &expression3;
    function.results.push_back (&result2);
    
    function.predicate_offsets.push_back (function.results.size ());
    function.branch_ends.push_back (function.results.size ());
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
    ASSERT_EQ (mu::core::error_type::arguments_are_disjoint, result.error->type ());
}

TEST (llvmc_analyzer, empty_call)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::ast::value value1 (&mu::llvmc::skeleton::the_unit_type);
    mu::llvmc::ast::unit unit1;
    function1.name = U"0";
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    mu::llvmc::ast::function function2;
    function2.name = U"1";
    mu::llvmc::ast::definite_expression expression1;
    expression1.arguments.push_back (&function1);
    expression1.set_predicate_position ();
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&expression1);
    function2.branch_ends.push_back (function2.results.size ());
    module1.functions.push_back (&function2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (2, result.module->functions.size ());
    auto function3 (result.module->functions [U"0"]);
    ASSERT_EQ (0, function3->parameters.size ());
    ASSERT_EQ (1, function3->results.size ());
    ASSERT_EQ (1, function3->branch_ends.size ());
    ASSERT_EQ (1, function3->branch_ends [0]);
    ASSERT_EQ (1, function3->predicate_offsets.size ());
    ASSERT_EQ (0, function3->predicate_offsets [0]);
    auto function4 (result.module->functions [U"1"]);
    ASSERT_EQ (0, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (0, function4->predicate_offsets [0]);
}

TEST (llvmc_analyzer, empty_call_predicate)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    mu::llvmc::ast::value value1 (&mu::llvmc::skeleton::the_unit_type);
    mu::llvmc::ast::unit unit1;
    function1.name = U"0";
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&unit1);
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    mu::llvmc::ast::function function2;
    function2.name = U"1";
    mu::llvmc::ast::function function3;
    function3.name = U"2";
    function3.predicate_offsets.push_back (function3.results.size ());
    function3.results.push_back (&unit1);
    function3.branch_ends.push_back (function3.results.size ());
    module1.functions.push_back (&function3);
    mu::llvmc::ast::definite_expression expression1;
    expression1.arguments.push_back (&function3);
    expression1.set_predicate_position ();
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&function1);
    expression2.set_predicate_position ();
    expression1.arguments.push_back (&expression2);
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.results.push_back (&expression1);
    function2.branch_ends.push_back (function2.results.size ());
    module1.functions.push_back (&function2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (3, result.module->functions.size ());
    auto function4 (result.module->functions [U"0"]);
    ASSERT_EQ (0, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (0, function4->predicate_offsets [0]);
    auto function5 (result.module->functions [U"1"]);
    ASSERT_EQ (0, function5->parameters.size ());
    ASSERT_EQ (1, function5->results.size ());
    ASSERT_EQ (1, function5->branch_ends.size ());
    ASSERT_EQ (1, function5->branch_ends [0]);
    ASSERT_EQ (1, function5->predicate_offsets.size ());
    ASSERT_EQ (0, function5->predicate_offsets [0]);
    auto function6 (result.module->functions [U"2"]);
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
    function1.name = U"0";
    mu::llvmc::skeleton::integer_type type1 (1);
    mu::llvmc::ast::value value1 (&type1);
    mu::llvmc::ast::parameter parameter1 (&value1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::result result1 (&value1);
    result1.value = &parameter1;
    function1.results.push_back (&result1);
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    mu::llvmc::ast::function function2;
    function2.name = U"1";
    mu::llvmc::ast::parameter parameter2 (&value1);
    function2.parameters.push_back (&parameter2);
    mu::llvmc::ast::definite_expression expression1;
    expression1.arguments.push_back (&function1);
    expression1.arguments.push_back (&parameter2);
    expression1.set_predicate_position ();
    mu::llvmc::ast::result result2 (&value1);
    result2.value = &expression1;
    function2.results.push_back (&result2);
    function2.predicate_offsets.push_back (function2.results.size ());
    function2.branch_ends.push_back (function2.results.size ());
    module1.functions.push_back (&function2);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (2, result.module->functions.size ());
    auto function3 (result.module->functions [U"0"]);
    ASSERT_EQ (1, function3->parameters.size ());
    ASSERT_EQ (1, function3->results.size ());
    ASSERT_EQ (1, function3->branch_ends.size ());
    ASSERT_EQ (1, function3->branch_ends [0]);
    ASSERT_EQ (1, function3->predicate_offsets.size ());
    ASSERT_EQ (1, function3->predicate_offsets [0]);
    auto function4 (result.module->functions [U"1"]);
    ASSERT_EQ (1, function4->parameters.size ());
    ASSERT_EQ (1, function4->results.size ());
    ASSERT_EQ (1, function4->branch_ends.size ());
    ASSERT_EQ (1, function4->branch_ends [0]);
    ASSERT_EQ (1, function4->predicate_offsets.size ());
    ASSERT_EQ (1, function4->predicate_offsets [0]);
}

TEST (llvmc_analyzer, set_expression_empty)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::set_expression set1;
    function1.results.push_back (&set1);
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (0, function2->results.size ());
    ASSERT_EQ (1, function2->predicate_offsets.size ());
    ASSERT_EQ (0, function2->predicate_offsets [0]);
    ASSERT_EQ (1, function2->branch_ends.size ());
    ASSERT_EQ (0, function2->branch_ends [0]);
}

TEST (llvmc_analyzer, set_expression_one)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::set_expression set1;
    mu::llvmc::ast::unit unit1;
    set1.items.push_back (&unit1);
    function1.results.push_back (&set1);
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
    ASSERT_EQ (0, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size ());
    ASSERT_EQ (1, function2->predicate_offsets.size ());
    ASSERT_EQ (0, function2->predicate_offsets [0]);
    ASSERT_EQ (1, function2->branch_ends.size ());
    ASSERT_EQ (1, function2->branch_ends [0]);
}

TEST (llvmc_analyzer, int_type1)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"1");
    mu::llvmc::ast::parameter parameter1 (&type1);
    function1.parameters.push_back (&parameter1);
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
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
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"1024");
    mu::llvmc::ast::parameter parameter1 (&type1);
    function1.parameters.push_back (&parameter1);
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
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
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"2000000000");
    mu::llvmc::ast::parameter parameter1 (&type1);
    function1.parameters.push_back (&parameter1);
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, ptr_type)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"1024");
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function1.parameters.push_back (&parameter1);
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
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
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"1");;
    mu::llvmc::ast::parameter parameter1 (&type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value value1 (&marker1);
    expression1.arguments.push_back (&value1);
    expression1.arguments.push_back (&parameter1);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::result result1 (&type1);
    result1.value = &expression1;
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size () == 1);
    auto result2 (function2->results [0]);
}

TEST (llvmc_analyzer, constant_int)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    function1.predicate_offsets.push_back (function1.results.size ());
    mu::llvmc::ast::number number1 (U"42");
    mu::llvmc::ast::constant_int constant1 (U"32", &number1);
    function1.results.push_back (&constant1);
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
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

TEST (llvmc_analyzer, instruction_store)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"1");;
    mu::llvmc::ast::parameter parameter1 (&type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter2 (&type2);
    function1.parameters.push_back (&parameter2);
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::store);
    mu::llvmc::ast::value value1 (&marker1);
    expression1.arguments.push_back (&value1);
    expression1.arguments.push_back (&parameter1);
    expression1.arguments.push_back (&parameter2);
    expression1.set_predicate_position ();
    mu::llvmc::ast::result result1 (&type1);
    result1.value = &expression1;
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
    ASSERT_EQ (2, function2->parameters.size ());
}

TEST (llvmc_analyzer, instruction_load)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"1");;
    mu::llvmc::ast::pointer_type type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::load);
    mu::llvmc::ast::value value1 (&marker1);
    expression1.arguments.push_back (&value1);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::result result1 (&type1);
    result1.value = &expression1;
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
    ASSERT_EQ (1, function2->parameters.size ());
}

TEST (llvmc_analyzer, instruction_icmp_eq)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    mu::llvmc::ast::integer_type type1 (U"8");
    mu::llvmc::ast::parameter parameter1 (&type1);
    function1.parameters.push_back (&parameter1);
    mu::llvmc::ast::definite_expression expression1;
    mu::llvmc::skeleton::marker marker1 (mu::llvmc::instruction_type::icmp);
    mu::llvmc::ast::value value1 (&marker1);
	mu::llvmc::skeleton::predicate predicate1 (mu::llvmc::predicates::icmp_eq);
	mu::llvmc::ast::value value2 (&predicate1);
    expression1.arguments.push_back (&value1);
    expression1.arguments.push_back (&value2);
    expression1.arguments.push_back (&parameter1);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::result result1 (&type1);
    result1.value = &expression1;
    function1.results.push_back (&result1);
    function1.branch_ends.push_back (function1.results.size ());
    function1.predicate_offsets.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
    ASSERT_EQ (1, function2->parameters.size ());
    ASSERT_EQ (1, function2->results.size ());
    auto result2 (dynamic_cast <mu::llvmc::skeleton::result *> (function2->results [0]));
    ASSERT_NE (nullptr, result2);
    auto instruction (dynamic_cast <mu::llvmc::skeleton::instruction *> (result2->value));
    ASSERT_NE (nullptr, instruction);
    ASSERT_EQ (4, instruction->arguments.size ());
    auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (instruction->type ()));
    ASSERT_NE (nullptr, type2);
    ASSERT_EQ (1, type2->bits);
}

TEST (llvmc_analyzer, multibranch_call)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    function.name = U"0";
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::skeleton::integer_type type3 (1);
    mu::llvmc::ast::value type4 (&type3);
    mu::llvmc::ast::parameter parameter1 (&type4);
    function.parameters.push_back (&parameter1);
    mu::llvmc::skeleton::marker if_marker (mu::llvmc::instruction_type::if_i);
    mu::llvmc::ast::value if_ast (&if_marker);
    mu::llvmc::ast::definite_expression expression1;
    expression1.arguments.push_back (&if_ast);
    expression1.arguments.push_back (&parameter1);
    expression1.set_predicate_position ();
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &element1;
    function.results.push_back (&result1);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &element2;
    function.results.push_back (&result2);
    function.branch_ends.push_back (function.results.size ());
    function.predicate_offsets.push_back (function.results.size ());
    module.functions.push_back (&function);	
	
    mu::llvmc::ast::function function2;
    function2.name = U"0";
    mu::llvmc::ast::parameter parameter2 (&type4);
    function2.parameters.push_back (&parameter2);
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&function);
    expression2.arguments.push_back (&parameter2);
    expression2.set_predicate_position ();
    mu::llvmc::ast::element element3 (&expression2, 0, 2);
    mu::llvmc::ast::element element4 (&expression2, 1, 2);
    mu::llvmc::ast::result result3 (&type2);
    result3.value = &element3;
    function2.results.push_back (&result3);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    mu::llvmc::ast::result result4 (&type2);
    result4.value = &element4;
    function2.results.push_back (&result4);
    function2.branch_ends.push_back (function2.results.size ());
    function2.predicate_offsets.push_back (function2.results.size ());
    module.functions.push_back (&function2);
	
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
}

TEST (llvmc_analyzer, loop_empty)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    mu::llvmc::ast::loop loop1;
    loop1.set_argument_offset ();
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&loop1);
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function2 (result.module->functions [U"0"]);
	ASSERT_NE (nullptr, function2);
	ASSERT_EQ (1, function2->results.size ());
	auto element1 (dynamic_cast <mu::llvmc::skeleton::loop_element_unit *> (function2->results [0]));
	ASSERT_NE (nullptr, element1);
    ASSERT_EQ (0, element1->source->argument_predicate_offset);
}

TEST (llvmc_analyzer, fail_loop_inner_error)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module1;
    mu::llvmc::ast::function function1;
    function1.name = U"0";
    mu::llvmc::ast::loop loop1;
    loop1.set_argument_offset ();
    mu::llvmc::ast::definite_expression expression1;
    loop1.results.push_back (&expression1);
    loop1.add_predicate_offset ();
    loop1.add_branch_end ();
    function1.predicate_offsets.push_back (function1.results.size ());
    function1.results.push_back (&loop1);
    function1.branch_ends.push_back (function1.results.size ());
    module1.functions.push_back (&function1);
    auto result (analyzer.analyze (&module1));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}