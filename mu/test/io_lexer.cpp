#include <gtest/gtest.h>

#include <mu/core/types.hpp>
#include <mu/core/string_hash.hpp>
#include <mu/core/lexer.hpp>
#include <mu/core/stream_istream.hpp>
#include <mu/core/tokens.hpp>

TEST (stringref, basic)
{
	std::array <uint8_t, 2> data;
	data [0] = 0xcc;
	data [1] = 0xdd;
	mu::io::string_range string1 (data.data (), data.data () + data.size ());
	auto string2 (string1.substr (1, 2));
	auto string3 (string1.substr (1));
	ASSERT_EQ (string1.end (), string2.end ());
	ASSERT_EQ (string1.begin () + 1, string2.begin ());
	ASSERT_EQ (string2, string3);
	ASSERT_NE (string1, string2);
	ASSERT_EQ (2, string1.size ());
	ASSERT_FALSE (string1.empty ());
	ASSERT_EQ (1, string2.size ());
	ASSERT_EQ (0xcc, string1 [0]);
	ASSERT_EQ (0xdd, string1 [1]);
	ASSERT_EQ (0xdd, string2 [0]);
	data [1] = 0xee;
	ASSERT_EQ (0xee, string3 [0]);
}

TEST (stringrange, convert)
{
	std::string text1 ("text1");
	auto string1 (text1);
	auto text2 ("text2");
	auto string2 (text2);
	ASSERT_NE (string1, string2);
}

TEST (io_lexer, empty)
{
    std::string text ("");
    mu::io::lexer lexer (text);
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
    std::string text ("[");
    mu::io::lexer lexer (text);
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
    std::string text ("]");
    mu::io::lexer lexer (text);
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
    std::string text (";");
    mu::io::lexer lexer (text);
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
    mu::io::lexer lexer (text.str ());
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
    std::string text (":/\n;");
    mu::io::lexer lexer (text);
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
    std::string text (":*junk*:;");
    mu::io::lexer lexer (text);
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
    std::string text ("a");
    mu::io::lexer lexer (text);
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
    std::string text ("a;");
    mu::io::lexer lexer (text);
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
    std::string text ("a[");
    mu::io::lexer lexer (text);
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
    std::string text ("a]");
    mu::io::lexer lexer (text);
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
    std::string text ("a b");
    mu::io::lexer lexer (text);
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
    text << ":[:]:;:::\t:t:\n:n:\f:f:\r:r:0";
    text << ':';
    text << '\0';
    mu::io::lexer lexer (text.str ());
    auto token1 (lexer.lex ());
    EXPECT_EQ (nullptr, token1.error);
    EXPECT_NE (nullptr, token1.token);
    auto token2 (dynamic_cast <mu::io::identifier *> (token1.token));
    ASSERT_NE (nullptr, token2);
    EXPECT_EQ (mu::core::region (0, 1, 1, 27, 4, 6), token2->region);
    ASSERT_EQ (14, token2->string.size ());
    EXPECT_EQ (U'[', token2->string [0]);
    EXPECT_EQ (U']', token2->string [1]);
    EXPECT_EQ (U';', token2->string [2]);
    EXPECT_EQ (U':', token2->string [3]);
    EXPECT_EQ (U'\t', token2->string [4]);
    EXPECT_EQ (U'\t', token2->string [5]);
    EXPECT_EQ (U'\n', token2->string [6]);
    EXPECT_EQ (U'\n', token2->string [7]);
    EXPECT_EQ (U'\f', token2->string [8]);
    EXPECT_EQ (U'\f', token2->string [9]);
    EXPECT_EQ (U'\r', token2->string [10]);
    EXPECT_EQ (U'\r', token2->string [11]);
    EXPECT_EQ (U'\0', token2->string [12]);
    EXPECT_EQ (U'\0', token2->string [13]);
    auto token3 (lexer.lex ());
    EXPECT_EQ (nullptr, token3.error);
    EXPECT_NE (nullptr, token3.token);
    auto token4 (dynamic_cast <mu::io::end *> (token3.token));
    ASSERT_NE (nullptr, token4);
    EXPECT_EQ (mu::core::region (28, 4, 7, 28, 4, 7), token4->region);
}

TEST (io_lexer, ascii_numbers)
{
    std::string text (":a00");
    mu::io::lexer lexer (text);
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
    std::string text (":a4A");
    mu::io::lexer lexer (text);
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
    std::string text (":a4a");
    mu::io::lexer lexer (text);
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
    std::string text (":uaaaabbbb");
    mu::io::lexer lexer (text);
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
    std::string text ("a:*junk*:b");
    mu::io::lexer lexer (text);
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
    std::string text ("a:*:*junk*:*:b");
    mu::io::lexer lexer (text);
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
    std::string text ("{}");
    mu::io::lexer lexer (text);
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
    mu::io::lexer lexer (text.str ());
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
    std::string text (":z");
    mu::io::lexer lexer (text);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_ascii)
{
    std::string text (":aqq");
    mu::io::lexer lexer (text);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_region_comment)
{
    std::string text (":*");
    mu::io::lexer lexer (text);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_ascii)
{
    std::string text (":a");
    mu::io::lexer lexer (text);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, invalid_eof_in_complex_identifier)
{
    std::string text ("{a}");
    mu::io::lexer lexer (text);
    auto token1 (lexer.lex ());
    EXPECT_NE (nullptr, token1.error);
    EXPECT_EQ (nullptr, token1.token);
}

TEST (io_lexer, hash_empty)
{
    mu::string string;
    mu::core::string_hash hash (string);
    auto text (hash.text());
    ASSERT_EQ (U"5049d74780a3e07d4202ab47d4cef2f4", text);
}

TEST (io_lexer, hash_sentence)
{
    mu::string string (U"The quick brown fox jumps over the lazy dog");
    mu::core::string_hash hash (string);
    auto text (hash.text());
    ASSERT_EQ (U"e32e5d57dfbb310c2b90a934f1d30625", text);
}

TEST (io_lexer, region_comment_containing_control_character)
{
    std::string text (":*:a00*:;");
    mu::io::lexer lexer (text);
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
