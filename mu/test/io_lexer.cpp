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
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token4->region);
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
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), token4->region);
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
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), token4->region);
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
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), token4->region);
}

TEST (io_lexer, whitespace)
{
    std::stringstream text;
    text << " \f\n\r\t";
    text << '\0';
    text << ';';
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (6, 4, 3, 6, 4, 3), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (7, 4, 4, 7, 4, 4), token4->region);
}

TEST (io_lexer, line_comment)
{
    std::stringstream text (":-\n;");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (3, 2, 1, 3, 2, 1), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (4, 2, 2, 4, 2, 2), token4->region);
}

TEST (io_lexer, region_comment)
{
    std::stringstream text (":(junk:);");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (8, 1, 9, 8, 1, 9), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (9, 1, 10, 9, 1, 10), token4->region);
}

TEST (io_lexer, identifier)
{
    std::stringstream text ("a");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), token4->region);
}

TEST (io_lexer, identifier_terminator)
{
    std::stringstream text ("a;");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::terminator *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), token4->region);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    ASSERT_NE (nullptr, token6);
    EXPECT_EQ (mu::core::region (2, 1, 3, 2, 1, 3), token6->region);
}

TEST (io_lexer, identifier_left_square)
{
    std::stringstream text ("a[");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::left_square *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), token4->region);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    ASSERT_NE (nullptr, token6);
    EXPECT_EQ (mu::core::region (2, 1, 3, 2, 1, 3), token6->region);
}

TEST (io_lexer, identifier_right_square)
{
    std::stringstream text ("a]");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::right_square *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), token4->region);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    ASSERT_NE (nullptr, token6);
    EXPECT_EQ (mu::core::region (2, 1, 3, 2, 1, 3), token6->region);
}

TEST (io_lexer, two_identifiers)
{
    std::stringstream text ("a b");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 0, 1, 1), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::identifier *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (2, 1, 3, 2, 1, 3), token4->region);
    ASSERT_EQ (1, token4->string.size ());
    EXPECT_EQ (U'b', token4->string [0]);
    auto token5 (lexer.lex ());
    EXPECT_EQ (nullptr, token5.error);
    EXPECT_NE (nullptr, token5.token);
    auto token6 (dynamic_cast <mu::io::end *> (token5.token));
    ASSERT_NE (nullptr, token6);
    EXPECT_EQ (mu::core::region (3, 1, 4, 3, 1, 4), token6->region);
}

TEST (io_lexer, escape_sequences)
{
    std::stringstream text;
    text << ":[:]:;:::\t:\n:\f:\r";
    text << ':';
    text << '\0';
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 17, 4, 2), token2->region);
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
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (18, 4, 3, 18, 4, 3), token4->region);
}

TEST (io_lexer, ascii_numbers)
{
    std::stringstream text (":a00");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 3, 1, 4), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ ('\0', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (4, 1, 5, 4, 1, 5), token4->region);
}

TEST (io_lexer, ascii_upper_letters)
{
    std::stringstream text (":a4A");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 3, 1, 4), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'\U0000004a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (4, 1, 5, 4, 1, 5), token4->region);
}

TEST (io_lexer, ascii_lower_letters)
{
    std::stringstream text (":a4a");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 3, 1, 4), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ (U'\U0000004a', token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (4, 1, 5, 4, 1, 5), token4->region);
}

TEST (io_lexer, unicode)
{
    std::stringstream text (":uaaaabbbb");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 9, 1, 10), token2->region);
    ASSERT_EQ (1, token2->string.size ());
    EXPECT_EQ ((char32_t)0xaaaabbbb, token2->string [0]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (10, 1, 11, 10, 1, 11), token4->region);
}

TEST (io_lexer, identifier_inner_comment)
{
    std::stringstream text ("a:(junk:)b");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 9, 1, 10), token2->region);
    ASSERT_EQ (2, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    EXPECT_EQ (U'b', token2->string [1]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (10, 1, 11, 10, 1, 11), token4->region);
}

TEST (io_lexer, nested_comment)
{
    std::stringstream text ("a:(:(junk:):)b");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 13, 1, 14), token2->region);
    ASSERT_EQ (2, token2->string.size ());
    EXPECT_EQ (U'a', token2->string [0]);
    EXPECT_EQ (U'b', token2->string [1]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (14, 1, 15, 14, 1, 15), token4->region);
}

TEST (io_lexer, empty_complex)
{
    std::stringstream text ("{}");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 1, 1, 2), token2->region);
    ASSERT_EQ (0, token2->string.size ());
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (2, 1, 3, 2, 1, 3), token4->region);
}

TEST (io_lexer, complex_with_control)
{
    std::stringstream text;
    text << "{a}[];: \n\t\r\f";
    text << '\0';
    text << 'a';
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 13, 4, 2), token2->region);
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
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (14, 4, 3, 14, 4, 3), token4->region);
}

TEST (io_lexer, invalid_control)
{
    std::stringstream text (":z");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_ascii)
{
    std::stringstream text (":aqq");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_region_comment)
{
    std::stringstream text (":(");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_ascii)
{
    std::stringstream text (":a");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_complex_identifier)
{
    std::stringstream text ("{a}");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, hash_empty)
{
    mu::string string;
    mu::io::string_hash hash (string);
    auto text (hash.text());
    ASSERT_EQ (U"00000000000000000000000000000000", text);
}

TEST (io_lexer, hash_sentence)
{
    mu::string string (U"The quick brown fox jumps over the lazy dog");;
    mu::io::string_hash hash (string);
    auto text (hash.text());
    ASSERT_EQ (U"09c3a5f1fb1a2f77a1db4872ccb04989", text);
}

TEST (io_lexer, region_comment_containing_control_character)
{
    std::stringstream text (":(:a00:);");
    mu::io::stream_istream stream (text, 16);
    mu::io::lexer lexer (stream);
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::terminator *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (8, 1, 9, 8, 1, 9), token2->region);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (9, 1, 10, 9, 1, 10), token4->region);
}