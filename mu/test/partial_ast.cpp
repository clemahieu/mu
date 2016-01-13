#include <gtest/gtest.h>

#include <mu/io/stream_istream.hpp>
#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/io/tokens.hpp>
#include <mu/core/string_hash.hpp>

class test_parser
{
public:
    test_parser (char const * const text_a):
    lexer (text_a),
    stream_token (lexer, 2),
    parser (stream_token)
    {
    };
    mu::io::lexer lexer;
    mu::io::stream_token stream_token;
    mu::llvmc::parser parser;
};

TEST (partial_ast, empty)
{
    test_parser parser ("");
    auto token (parser.parser.peek ());
    ASSERT_NE (nullptr, token.token);
    auto end (dynamic_cast <mu::io::end *> (token.token));
    EXPECT_NE (nullptr, end);
}

TEST (partial_ast, tokens)
{
    test_parser parser ("]a;");
    auto token1 (parser.parser.peek ());
    ASSERT_NE (nullptr, token1.token);
    auto right_square (dynamic_cast <mu::io::right_square *> (token1.token));
    EXPECT_NE (nullptr, right_square);
    auto token2 (parser.parser.peek ());
    auto identifier (dynamic_cast <mu::io::identifier *> (token2.token));
    EXPECT_NE (nullptr, identifier);
    auto token3 (parser.parser.peek ());
    auto terminator (dynamic_cast <mu::io::terminator *> (token3.token));
    EXPECT_NE (nullptr, terminator);
}