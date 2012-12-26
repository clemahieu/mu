#include <gtest/gtest.h>

#include <mu/core/types.hpp>
#include <mu/io/lexer.hpp>
#include <mu/io/stream_istream.hpp>
#include <mu/io/tokens.hpp>

TEST (io_lexer, empty)
{
    std::stringstream text ("");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::end *> (token1.token));
    EXPECT_NE (nullptr, token2);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, left_square)
{
    std::stringstream text ("[");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::left_square *> (token1.token));
    EXPECT_NE (nullptr, token2);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, right_square)
{
    std::stringstream text ("]");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::right_square *> (token1.token));
    EXPECT_NE (nullptr, token2);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, terminator)
{
    std::stringstream text (";");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    EXPECT_NE (nullptr, token2);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, whitespace)
{
    std::stringstream text (" \f\n\r\t");
    text << '\0';
    text << ';';
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    EXPECT_NE (nullptr, token2);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}