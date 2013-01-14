#include <gtest/gtest.h>

#include <mu/llvmc/partial_ast.hpp>

#include <mu/io/stream_muistream.hpp>
#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/io/tokens.hpp>

class test_parser
{
public:
    test_parser (char32_t const * const text_a):
    text (text_a),
    stream (text, 16),
    lexer (stream),
    stream_token (lexer, 2),
    parser (stream_ast),
    stream_ast (stream_token, parser)
    {
    };
    mu::stringstream text;
    mu::io::stream_muistream stream;
    mu::io::lexer lexer;
    mu::io::stream_token stream_token;
    mu::llvmc::parser parser;
    mu::llvmc::partial_ast stream_ast;
};

TEST (partial_ast, empty)
{
    test_parser parser (U"");
    auto token (parser.stream_ast.peek ());
    ASSERT_NE (nullptr, token.token);
    auto end (dynamic_cast <mu::io::end *> (token.token));
    EXPECT_NE (nullptr, end);
}

TEST (partial_ast, tokens)
{
    test_parser parser (U"]a;");
    auto token1 (parser.stream_ast.peek ());
    ASSERT_NE (nullptr, token1.token);
    auto right_square (dynamic_cast <mu::io::right_square *> (token1.token));
    EXPECT_NE (nullptr, right_square);
    parser.stream_ast.consume ();
    auto token2 (parser.stream_ast.peek ());
    auto identifier (dynamic_cast <mu::io::identifier *> (token2.token));
    EXPECT_NE (nullptr, identifier);
    parser.stream_ast.consume ();
    auto token3 (parser.stream_ast.peek ());
    auto terminator (dynamic_cast <mu::io::terminator *> (token3.token));
    EXPECT_NE (nullptr, terminator);
}