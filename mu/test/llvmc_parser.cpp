#include <gtest/gtest.h>

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_muistream.hpp>
#include <mu/llvmc/ast.hpp>

#include <gc_cpp.h>

class test_parser
{
public:
    test_parser (char32_t const * const text_a):
    text (text_a),
    stream (text, 16),
    lexer (stream),
    stream_token (lexer, 2),
    parser (stream_token)
    {        
    };
    mu::stringstream text;
    mu::io::stream_muistream stream;
    mu::io::lexer lexer;
    mu::io::stream_token stream_token;
    mu::llvmc::parser parser;
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
    mu::llvmc::mapping mapping;
    auto keyword1 (mapping.get_hook (mu::string (U"keyword")));
    EXPECT_EQ (nullptr, keyword1.hook);
}

TEST (llvmc_parser, mapping_get_covered)
{
    test_non_covering keyword1;
    mu::llvmc::mapping mapping;
    auto error (mapping.map (mu::string (U"non-covered"), &keyword1));
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
    mu::llvmc::mapping mapping;
    auto error (mapping.map (mu::string (U"covered"), &keyword1));
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
    mu::llvmc::mapping mapping;
    auto error1 (mapping.map (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    mu::llvmc::ast::node node;
    auto error2 (mapping.map (mu::string (U"covered1"), &node));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, mapping_insert_covering_existing)
{
    test_covering keyword1;
    mu::llvmc::mapping mapping;
    auto error1 (mapping.map (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    mu::llvmc::ast::node node;
    auto error2 (mapping.map (mu::string (U"covered1"), &node));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, empty)
{
    test_parser parser (U"");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    EXPECT_EQ (0, module2->functions.size ());
}

TEST (llvmc_parser, fail_unexpected)
{
    test_parser parser (U"[");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, simple)
{
    test_parser parser (U"function test [] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->functions.size ());
}