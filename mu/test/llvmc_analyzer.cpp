#include <gtest/gtest.h>

#include <mu/llvmc/analyzer.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/skeleton.hpp>

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
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [0]);
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
}

TEST (llvmc_analyzer, single_parameter)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function.parameters.push_back (&parameter1);
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [0]);
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
    mu::llvmc::skeleton::unit_type type1;
    mu::llvmc::ast::value type2 (&type1);
    mu::llvmc::ast::parameter parameter1 (&type2);
    function.parameters.push_back (&parameter1);
    function.results.push_back (decltype (function.results)::value_type ());
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &parameter1;
    function.results [0].push_back (&result1);
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [0]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (function1->parameters [0]);
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->results [0].size ());
    auto result2 (function1->results [0][0]);
    auto result3 (dynamic_cast <mu::llvmc::skeleton::value *> (result2->value));
    ASSERT_NE (nullptr, result3);
    ASSERT_EQ (parameter2, result3);
    ASSERT_EQ (function1->entry, result2->value->branch);
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
    function.results.push_back (decltype (function.results)::value_type ());
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &parameter1;
    function.results [0].push_back (&result1);
    function.results.push_back (decltype (function.results)::value_type ());
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &parameter1;
    function.results [1].push_back (&result2);
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_NE (nullptr, result.error);
    ASSERT_EQ (nullptr, result.module);
}

TEST (llvmc_analyzer, if_instruction)
{
    mu::llvmc::analyzer analyzer;
    mu::llvmc::ast::module module;
    mu::llvmc::ast::function function;
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
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    function.results.push_back (decltype (function.results)::value_type ());
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &element1;
    function.results [0].push_back (&result1);
    function.results.push_back (decltype (function.results)::value_type ());
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &element2;
    function.results [1].push_back (&result2);
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [0]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter2 (function1->parameters [0]);
    ASSERT_EQ (2, function1->results.size ());
    ASSERT_EQ (1, function1->results [0].size ());
    auto result3 (function1->results [0][0]);
    auto element3 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (result3->value));
    ASSERT_NE (nullptr, element3);
    ASSERT_EQ (1, function1->results [1].size ());
    auto result4 (function1->results [1][0]);
    auto element4 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (result4->value));
    ASSERT_EQ (element3->source, element4->source);
    ASSERT_EQ (parameter2, element3->source->predicate);
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
    mu::llvmc::ast::element element1 (&expression1, 0, 2);
    mu::llvmc::ast::element element2 (&expression1, 1, 2);
    mu::llvmc::skeleton::marker add_marker (mu::llvmc::instruction_type::add);
    mu::llvmc::ast::value add_ast (&add_marker);    
    mu::llvmc::ast::definite_expression expression2;
    expression2.arguments.push_back (&element1);
    expression2.arguments.push_back (&add_ast);
    expression2.arguments.push_back (&parameter2);
    expression2.arguments.push_back (&parameter2);    
    mu::llvmc::ast::definite_expression expression3;
    expression3.arguments.push_back (&element2);
    expression3.arguments.push_back (&add_ast);
    expression3.arguments.push_back (&parameter3);
    expression3.arguments.push_back (&parameter3);    
    function.results.push_back (decltype (function.results)::value_type ());
    mu::llvmc::ast::result result1 (&type2);
    result1.value = &expression2;
    function.results [0].push_back (&result1);
    function.results.push_back (decltype (function.results)::value_type ());
    mu::llvmc::ast::result result2 (&type2);
    result2.value = &expression3;
    function.results [1].push_back (&result2);
    module.functions.push_back (&function);
    auto result (analyzer.analyze (&module));
    ASSERT_EQ (nullptr, result.error);
    ASSERT_NE (nullptr, result.module);
    ASSERT_EQ (1, result.module->functions.size ());
    auto function1 (result.module->functions [0]);
    ASSERT_EQ (3, function1->parameters.size ());
    auto parameter4 (function1->parameters [0]);
    auto parameter5 (function1->parameters [1]);
    auto parameter6 (function1->parameters [2]);
    ASSERT_EQ (2, function1->results.size ());
    ASSERT_EQ (1, function1->results [0].size ());
    auto result3 (function1->results [0][0]);
    auto element3 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result3->value));
    ASSERT_NE (nullptr, element3);
    ASSERT_EQ (mu::llvmc::instruction_type::add, element3->type_m);
    ASSERT_EQ (3, element3->arguments.size ());
    ASSERT_EQ (&add_marker, element3->arguments [0]);
    ASSERT_EQ (parameter5, element3->arguments [1]);
    ASSERT_EQ (parameter5, element3->arguments [2]);
    ASSERT_EQ (1, element3->predicates.size ());
    ASSERT_EQ (1, function1->results [1].size ());
    auto result4 (function1->results [1][0]);
    auto element4 (dynamic_cast <mu::llvmc::skeleton::instruction *> (result4->value));
    ASSERT_NE (nullptr, element4);
    ASSERT_EQ (mu::llvmc::instruction_type::add, element4->type_m);
    ASSERT_EQ (3, element4->arguments.size ());
    ASSERT_EQ (&add_marker, element4->arguments [0]);
    ASSERT_EQ (parameter6, element4->arguments [1]);
    ASSERT_EQ (parameter6, element4->arguments [2]);
    ASSERT_EQ (1, element4->predicates.size ());
    ASSERT_NE (element3->branch, element4->branch);
    auto element5 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (element3->predicates [0]));
    ASSERT_NE (nullptr, element5);
    auto element6 (dynamic_cast <mu::llvmc::skeleton::switch_element *> (element4->predicates [0]));
    ASSERT_NE (nullptr, element6);
    ASSERT_NE (element5, element6);
    ASSERT_EQ (element5->source, element6->source);
    auto instruction1 (element5->source);
    ASSERT_EQ (0, instruction1->predicates.size ());
    ASSERT_EQ (parameter4, instruction1->predicate);
}