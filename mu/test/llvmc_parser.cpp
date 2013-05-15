#include <gtest/gtest.h>

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_istream.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/partial_ast.hpp>
#include <mu/core/error.hpp>
#include <mu/llvmc/skeleton.hpp>

#include <llvm/DerivedTypes.h>

#include <gc_cpp.h>

class test_parser
{
public:
    test_parser (char const * const text_a):
    text (text_a),
    stream (text, 16),
    lexer (stream),
    stream_token (lexer, 2),
    parser (stream_ast),
    stream_ast (stream_token, parser)
    {        
    };
    std::stringstream text;
    mu::io::stream_istream stream;
    mu::io::lexer lexer;
    mu::io::stream_token stream_token;
    mu::llvmc::parser parser;
    mu::llvmc::partial_ast stream_ast;
};

class test_non_covering : public mu::llvmc::hook
{
public:    
    mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser) override
    {
        return mu::llvmc::node_result {new (GC) mu::llvmc::ast::node, nullptr};
    }
    bool covering () override
    {
        return false;
    }
};

class test_covering : public mu::llvmc::hook
{
public:
    mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser) override
    {
        return mu::llvmc::node_result {new (GC) mu::llvmc::ast::node, nullptr};
    }
    bool covering () override
    {
        return true;
    }
};

TEST (llvmc_parser, mapping_get_hook)
{
    mu::llvmc::keywords mapping;
    auto keyword1 (mapping.get_hook (mu::string (U"keyword")));
    EXPECT_EQ (nullptr, keyword1.hook);
}

TEST (llvmc_parser, mapping_get_covered)
{
    test_non_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error (mapping.insert (mu::string (U"non-covered"), &keyword1));
    EXPECT_EQ (false, error);
    auto keyword2 (mapping.get_hook (mu::string (U"non-covered")));
    EXPECT_EQ (&keyword1, keyword2.hook);
    auto keyword3 (mapping.get_hook (mu::string (U"non-covered1")));
    EXPECT_EQ (nullptr, keyword3.hook);
    auto keyword4 (mapping.get_hook (mu::string (U"non-covere")));
    EXPECT_EQ (nullptr, keyword4.hook);
}

TEST (llvmc_parser, mapping_get_non_covered)
{
    test_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error);
    auto keyword2 (mapping.get_hook (mu::string (U"covered")));
    EXPECT_EQ (&keyword1, keyword2.hook);
    EXPECT_EQ (mu::string (U""), keyword2.data);
    auto keyword3 (mapping.get_hook (mu::string (U"covered1")));
    EXPECT_EQ (&keyword1, keyword3.hook);
    EXPECT_EQ (mu::string (U"1"), keyword3.data);
    auto keyword4 (mapping.get_hook (mu::string (U"covere")));
    EXPECT_EQ (nullptr, keyword4.hook);
}

TEST (llvmc_parser, mapping_insert_under_covered)
{
    test_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    test_non_covering keyword2;
    auto error2 (mapping.insert (mu::string (U"covered1"), &keyword2));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, mapping_insert_covering_existing)
{
    test_non_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered1"), &keyword1));
    EXPECT_EQ (false, error1);
    test_covering keyword2;
    auto error2 (mapping.insert (mu::string (U"covered"), &keyword2));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, global_check_non_covering)
{
    test_non_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    mu::llvmc::global global (&mapping);
    mu::llvmc::ast::unit unit1;
    auto error2 (global.insert (mu::string (U"covered"), &unit1));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, global_check_covering)
{
    test_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    mu::llvmc::global global (&mapping);
    mu::llvmc::ast::unit unit1;
    auto error2 (global.insert (mu::string (U"covered1"), &unit1));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, empty)
{
    test_parser parser ("");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    EXPECT_EQ (0, module2->functions.size ());
}

TEST (llvmc_parser, fail_no_expression_end)
{
    test_parser parser ("[");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, simple)
{
    test_parser parser ("function test [] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
}

TEST (llvmc_parser, DISABLED_recursive)
{
    test_parser parser ("function test1 [] [[test2]] [] function test2 [] [[test1]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (2, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
    ASSERT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function1->roots [0]));
    ASSERT_EQ (1, expression1->arguments.size ());
    auto function2 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [1]));
    ASSERT_NE (nullptr, function2);
    EXPECT_EQ (0, function2->parameters.size ());
    EXPECT_EQ (0, function2->results.size ());
    ASSERT_EQ (1, function2->roots.size ());
    auto expression2 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function2->roots [0]));
    ASSERT_EQ (1, expression2->arguments.size ());
    ASSERT_EQ (function2, expression1->arguments [0]);
    ASSERT_EQ (function1, expression2->arguments [0]);
}

TEST (llvmc_parser, two_functions)
{
    test_parser parser ("function test1 [] [] [] function test2 [] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (2, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
    auto function2 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [1]));
    ASSERT_NE (nullptr, function2);
    EXPECT_EQ (0, function2->parameters.size ());
    EXPECT_EQ (0, function2->results.size ());
}

TEST (llvmc_parser, int_type1)
{
    test_parser parser ("function test1 [int1 val] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_NE (nullptr, parameter1);
    auto value1 (dynamic_cast <mu::llvmc::ast::value *> (parameter1->type));
    ASSERT_NE (nullptr, value1);
    auto type1 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (value1->node_m));
    ASSERT_NE (nullptr, type1);
    EXPECT_EQ (1, type1->bits);
}

TEST (llvmc_parser, int_type1024)
{
    test_parser parser ("function test1024 [int1024 val] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_NE (nullptr, parameter1);
    auto value1 (dynamic_cast <mu::llvmc::ast::value *> (parameter1->type));
    ASSERT_NE (nullptr, value1);
    auto type1 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (value1->node_m));
    ASSERT_NE (nullptr, type1);
    EXPECT_EQ (1024, type1->bits);
}

TEST (llvmc_parser, fail_int_type2000000000)
{
    test_parser parser ("function test2000000000 [int2000000000 val] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    EXPECT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, fail_no_type)
{
    test_parser parser ("function test [int1 i] [] [[i]]");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    EXPECT_EQ (mu::core::error_type::expecting_result_reference, module1.error->type ());
    EXPECT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, block)
{
    mu::llvmc::keywords keywords;
    mu::llvmc::global global (&keywords);
    mu::llvmc::block block (&global);
    mu::llvmc::ast::node node;
    auto error (block.insert (mu::string (U"test"), &node));
    EXPECT_TRUE (!error);
    auto success (false);
    block.refer(mu::string (U"test"),
                [&success]
                (mu::llvmc::ast::node * node_a)
                {
                    success = true;
                });
    EXPECT_TRUE (success);
}

TEST (llvmc_parser, results1)
{
    test_parser parser ("function test1 [int1 val] [] [[int1 val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results1_empty_predicate)
{
    test_parser parser ("function test1 [int1 val] [] [[int1 val;]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results1_one_predicate)
{
    test_parser parser ("function test1 [int1 val] [] [[int1 val; val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (2, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (2, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results1_multi_predicate)
{
    test_parser parser ("function test1 [int1 val] [] [[int1 val; val val val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (4, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (4, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results2)
{
    test_parser parser ("function test1 [int1 val] [] [[int1 val] [int1 val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (2, function1->results.size ());
    ASSERT_EQ (2, function1->branch_ends.size ());
    ASSERT_EQ (2, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
    ASSERT_EQ (2, function1->branch_ends [1]);
    ASSERT_EQ (2, function1->predicate_offsets [1]);
    auto result2 (function1->results [1]);
    auto value2 (dynamic_cast <mu::llvmc::ast::result *> (result2));
    ASSERT_NE (nullptr, value2);
    EXPECT_EQ (parameter1, value2->value);
}

TEST (llvmc_parser, results2_predicates)
{
    test_parser parser ("function test1 [int1 val] [] [[int1 val; val] [int1 val; val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (4, function1->results.size ());
    ASSERT_EQ (2, function1->branch_ends.size ());
    ASSERT_EQ (2, function1->predicate_offsets.size ());
    ASSERT_EQ (2, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    ASSERT_EQ (value1->value, function1->results [1]);
    EXPECT_EQ (parameter1, value1->value);
    ASSERT_EQ (4, function1->branch_ends [1]);
    ASSERT_EQ (3, function1->predicate_offsets [1]);
    auto result2 (function1->results [2]);
    auto value2 (dynamic_cast <mu::llvmc::ast::result *> (result2));
    ASSERT_NE (nullptr, value2);
    ASSERT_EQ (value2->value, function1->results [3]);
    EXPECT_EQ (parameter1, value2->value);
}

TEST (llvmc_parser, body1)
{
    test_parser parser ("function test1 [int1 val] [[]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    EXPECT_EQ (0, root1->arguments.size ());
    ASSERT_EQ (0 - 1, root1->predicate_position);
}

TEST (llvmc_parser, body2)
{
    test_parser parser ("function test1 [int1 val] [[val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->arguments.size ());
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (0 - 1, root1->predicate_position);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
}

TEST (llvmc_parser, body3)
{
    test_parser parser ("function test1 [int1 val] [[val] [val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (2, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->arguments.size ());
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (0 - 1, root1->predicate_position);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
    auto root2 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function1->roots [1]));
    ASSERT_NE (nullptr, root2);
    ASSERT_EQ (1, root2->arguments.size ());
    auto argument2 (root2->arguments [0]);
    EXPECT_EQ (parameter1, argument2);
}

TEST (llvmc_parser, body4)
{
    test_parser parser ("function test1 [int1 val] [[val;val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (2, root1->arguments.size ());
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (1, root1->predicate_position);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
}

TEST (llvmc_parser, fail_body5)
{
    test_parser parser ("function test1 [int1 val] [[val;;val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::error_type::already_parsing_predicates, module1.error->type());
}

TEST (llvmc_parser, set1)
{
    test_parser parser ("function test1 [int1 val] [set val1 [val]] [[int1 val1]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::definite_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->arguments.size ());
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    EXPECT_EQ (root1, value1->value);
}

TEST (llvmc_parser, if1)
{
    test_parser parser ("function test1 [int1 val] [if [] [] []] [[int1 val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::if_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (0, root1->true_roots.size ());
    ASSERT_EQ (0, root1->false_roots.size ());
}

TEST (llvmc_parser, if2)
{
    test_parser parser ("function test1 [int1 val] [if [] [set val1 [val]] [set val2 [val]]] [[int1 val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::if_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->true_roots.size ());
    ASSERT_EQ (1, root1->false_roots.size ());
}

TEST (llvmc_parser, loop1)
{
    test_parser parser ("function test1 [] [loop [] [] [] []] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::loop *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    EXPECT_EQ (0, root1->arguments.size ());
    EXPECT_EQ (0, root1->parameters.size ());
    EXPECT_EQ (0, root1->roots.size ());
    EXPECT_EQ (0, root1->results.size ());
}

TEST (llvmc_parser, loop2)
{
    test_parser parser ("function test1 [int1 val] [loop [val] [val1] [[val1]] [[val val1]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (function1->parameters [0]);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::loop *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->arguments.size ());
    EXPECT_EQ (parameter1, root1->arguments [0]);
    ASSERT_EQ (1, root1->parameters.size ());
    auto parameter2 (root1->parameters [0]);
    ASSERT_EQ (1, root1->roots.size ());
    auto root2 (dynamic_cast <mu::llvmc::ast::definite_expression *> (root1->roots [0]));
    ASSERT_NE (nullptr, root2);
    ASSERT_EQ (1, root2->arguments.size ());
    EXPECT_EQ (parameter2, root2->arguments [0]);
    ASSERT_EQ (1, root1->results.size ());
    ASSERT_EQ (2, root1->results [0].size ());
    ASSERT_EQ (parameter1, root1->results [0] [0]);
    ASSERT_EQ (parameter2, root1->results [0] [1]);
}

TEST (llvmc_parser, let1)
{
    test_parser parser ("function test1 [int1 val] [let val1 [val]] [[int1 val1]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (module2->functions [0]));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::set_expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (1, expression1->items.size ());
    auto argument1 (expression1->items [0]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    auto element1 (dynamic_cast <mu::llvmc::ast::element *> (value1->value));
    ASSERT_NE (nullptr, element1);
    ASSERT_EQ (expression1, element1->node);
    ASSERT_EQ (0, element1->index);
    ASSERT_EQ (1, element1->total);
}
