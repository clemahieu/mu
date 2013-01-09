#include <gtest/gtest.h>

#include <mu/core/types.hpp>
#include <mu/io/lexer.hpp>
#include <mu/io/stream_muistream.hpp>
#include <mu/io/tokens.hpp>

TEST (io_lexer, empty)
{
    mu::stringstream text (U"");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::end *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::io::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_EQ (mu::io::region (0, 1, 1, 0, 1, 1), token4->region);
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, left_square)
{
    mu::stringstream text (U"[");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::left_square *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::io::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::io::region (1, 1, 2, 1, 1, 2), token4->region);
}

TEST (io_lexer, right_square)
{
    mu::stringstream text (U"]");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::right_square *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::io::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::io::region (1, 1, 2, 1, 1, 2), token4->region);
}

TEST (io_lexer, terminator)
{
    mu::stringstream text (U";");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::io::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::io::region (1, 1, 2, 1, 1, 2), token4->region);
}

TEST (io_lexer, whitespace)
{
    mu::stringstream text;
    text << U" \f\n\r\t";
    text << U'\0';
    text << U';';
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::io::region (6, 4, 3, 6, 4, 3), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::io::region (7, 4, 4, 7, 4, 4), token4->region);
}

TEST (io_lexer, line_comment)
{
    mu::stringstream text (U":-\n;");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::io::region (3, 2, 1, 3, 2, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::io::region (4, 2, 2, 4, 2, 2), token4->region);
}

TEST (io_lexer, region_comment)
{
    mu::stringstream text (U":(junk:);");
    mu::io::stream_muistream stream (text, 16);
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

TEST (io_lexer, identifier)
{
    mu::stringstream text (U"a");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, identifier_terminator)
{
    mu::stringstream text (U"a;");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::terminator *> (token3.token));
    EXPECT_NE (nullptr, token4);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    EXPECT_NE (nullptr, token6);
}

TEST (io_lexer, identifier_left_square)
{
    mu::stringstream text (U"a[");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::left_square *> (token3.token));
    EXPECT_NE (nullptr, token4);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    EXPECT_NE (nullptr, token6);
}

TEST (io_lexer, identifier_right_square)
{
    mu::stringstream text (U"a]");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::right_square *> (token3.token));
    EXPECT_NE (nullptr, token4);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    EXPECT_NE (nullptr, token6);
}

TEST (io_lexer, two_identifiers)
{
    mu::stringstream text (U"a b");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::identifier *> (token3.token));
    EXPECT_NE (nullptr, token4);
    ASSERT_EQ (1, token4->string.size ());
    EXPECT_EQ (U'b', token4->string [0]);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    EXPECT_NE (nullptr, token6);
}

TEST (io_lexer, escape_sequences)
{
    mu::stringstream text;
    text << U":[:]:;:::\t:\n:\f:\r";
    text << U':';
    text << U'\0';
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    ASSERT_EQ (9, token2->string.size ());
    EXPECT_EQ (U'[', token2->string [0]);
    EXPECT_EQ (U']', token2->string [1]);
    EXPECT_EQ (U';', token2->string [2]);
    EXPECT_EQ (U':', token2->string [3]);
    EXPECT_EQ (U'\t', token2->string [4]);
    EXPECT_EQ (U'\n', token2->string [5]);
    EXPECT_EQ (U'\f', token2->string [6]);
    EXPECT_EQ (U'\r', token2->string [7]);
    EXPECT_EQ (U'\0', token2->string [8]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, ascii_numbers)
{
    mu::stringstream text (U":a00");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'\U00000000', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, ascii_upper_letters)
{
    mu::stringstream text (U":a4A");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'\U0000004a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, ascii_lower_letters)
{
    mu::stringstream text (U":a4a");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'\U0000004a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, unicode)
{
    mu::stringstream text (U":uaaaabbbb");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ ((char32_t)0xaaaabbbb, token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, identifier_inner_comment)
{
    mu::stringstream text (U"a:(junk:)b");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (2, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    EXPECT_EQ (U'b', token2->string [1]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, nested_comment)
{
    mu::stringstream text (U"a:(:(junk:):)b");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (2, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    EXPECT_EQ (U'b', token2->string [1]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, empty_complex)
{
    mu::stringstream text (U"{}");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (0, token2->string.size ());
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, complex_with_control)
{
    mu::stringstream text;
    text << U"{a}[];: \n\t\r\f";
    text << U'\0';
    text << U'a';
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    EXPECT_NE (nullptr, token2);
    ASSERT_EQ (10, token2->string.size ());
    EXPECT_EQ (U'[', token2->string [0]);
    EXPECT_EQ (U']', token2->string [1]);
    EXPECT_EQ (U';', token2->string [2]);
    EXPECT_EQ (U':', token2->string [3]);
    EXPECT_EQ (U' ', token2->string [4]);
    EXPECT_EQ (U'\n', token2->string [5]);
    EXPECT_EQ (U'\t', token2->string [6]);
    EXPECT_EQ (U'\r', token2->string [7]);
    EXPECT_EQ (U'\f', token2->string [8]);
    EXPECT_EQ (U'\0', token2->string [9]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_NE (nullptr, token4);
}

TEST (io_lexer, invalid_control)
{
    mu::stringstream text (U":z");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_ascii)
{
    mu::stringstream text (U":aqq");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_region_comment)
{
    mu::stringstream text (U":(");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_ascii)
{
    mu::stringstream text (U":a");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_complex_identifier)
{
    mu::stringstream text (U"{a}");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}