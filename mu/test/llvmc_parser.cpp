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

class test_non_dominator : public mu::llvmc::keyword
{
public:    
    mu::llvmc::node_result parse (mu::io::stream <mu::io::token *> & stream_a) override
    {
        return mu::llvmc::node_result {new (GC) mu::llvmc::ast::node, nullptr};
    }
    bool dominator () override
    {
        return false;
    }
};

class test_dominator : public mu::llvmc::keyword
{
public:
    mu::llvmc::node_result parse (mu::io::stream <mu::io::token *> & stream_a) override
    {
        return mu::llvmc::node_result {new (GC) mu::llvmc::ast::node, nullptr};
    }
    bool dominator () override
    {
        return true;
    }
};

TEST (llvmc_parser, mapping_get_keyword)
{
    mu::llvmc::mapping mapping;
    auto keyword1 (mapping.get_keyword (mu::string (U"keyword")));
    EXPECT_EQ (nullptr, keyword1);
}

TEST (llvmc_parser, mapping_get_dom)
{
    test_non_dominator keyword1;
    mu::llvmc::mapping mapping;
    mapping.mappings.insert (decltype (mapping.mappings)::value_type (mu::string (U"non-dom"), &keyword1));
    auto keyword2 (mapping.get_keyword (mu::string (U"non-dom")));
    EXPECT_EQ (&keyword1, keyword2);
    auto keyword3 (mapping.get_keyword (mu::string (U"non-dom1")));
    EXPECT_EQ (nullptr, keyword3);
    auto keyword4 (mapping.get_keyword (mu::string (U"non-do")));
    EXPECT_EQ (nullptr, keyword4);
}

TEST (llvmc_parser, mapping_get_non_dom)
{
    test_dominator keyword1;
    mu::llvmc::mapping mapping;
    mapping.mappings.insert (decltype (mapping.mappings)::value_type (mu::string (U"dom"), &keyword1));
    auto keyword2 (mapping.get_keyword (mu::string (U"dom")));
    EXPECT_EQ (&keyword1, keyword2);
    auto keyword3 (mapping.get_keyword (mu::string (U"dom1")));
    EXPECT_EQ (&keyword1, keyword3);
    auto keyword4 (mapping.get_keyword (mu::string (U"do")));
    EXPECT_EQ (nullptr, keyword4);
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