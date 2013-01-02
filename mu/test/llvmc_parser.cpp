#include <gtest/gtest.h>

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_muistream.hpp>
#include <mu/llvmc/ast.hpp>

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

TEST (llvmc_parser, empty)
{
    test_parser parser (U"");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.module);
    EXPECT_EQ (0, module1.module->functions.size ());
}

TEST (llvmc_parser, fail_unexpected)
{
    test_parser parser (U"[");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.module);
}

TEST (llvmc_parser, simple)
{
    test_parser parser (U"function test [] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.module);
    ASSERT_EQ (1, module1.module->functions.size ());
}