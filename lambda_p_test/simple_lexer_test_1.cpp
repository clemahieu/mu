#include "simple_lexer_test_1.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/serialization/simple_lexer.h>
#include <lambda_p/tokens/token.h>
#include <lambda_p/serialization/simple.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/complex_identifier.h>

#include <sstream>

lambda_p_test::simple_lexer_test_1::simple_lexer_test_1(void)
{
}

lambda_p_test::simple_lexer_test_1::~simple_lexer_test_1(void)
{
}

struct token_vector
{
	void operator () (::lambda_p::tokens::token * token)
	{
		tokens.push_back (token);
	}
	::std::vector < ::lambda_p::tokens::token *> tokens;
};

void lambda_p_test::simple_lexer_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
	run_10 ();
	run_11 ();
	run_12 ();
}

void lambda_p_test::simple_lexer_test_1::run_1 ()
{
	::std::wstringstream stream;
	::lambda_p::core::routine routine (0);
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (stream);
	serializer.routine (&routine);
	::std::wstring str (stream.str ());
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 3);
	assert (dynamic_cast < ::lambda_p::tokens::identifier *> (tokens.tokens [0]) != NULL);
	assert (dynamic_cast < ::lambda_p::tokens::statement_end *> (tokens.tokens [1]) != NULL);
	assert (dynamic_cast < ::lambda_p::tokens::routine_end *> (tokens.tokens [2]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_2 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L"routine0033F838\n");
	str.append (L";/junk12346680!@#$%^&*();astnhcheou\n");
	str.append (L";;\n");
	str.append (L";.\n");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 3);
	assert (dynamic_cast < ::lambda_p::tokens::identifier *> (tokens.tokens [0]) != NULL);
	assert (dynamic_cast < ::lambda_p::tokens::statement_end *> (tokens.tokens [1]) != NULL);
	assert (dynamic_cast < ::lambda_p::tokens::routine_end *> (tokens.tokens [2]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_3 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";/");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_4 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";*;*");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_5 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";*");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 1);
	assert (dynamic_cast < ::lambda_p::tokens::error *> (tokens.tokens [0]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_6 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";*;");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 1);
	assert (dynamic_cast < ::lambda_p::tokens::error *> (tokens.tokens [0]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_7 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";\"");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 1);
	assert (dynamic_cast < ::lambda_p::tokens::error *> (tokens.tokens [0]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_8 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";\";");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 1);
	assert (dynamic_cast < ::lambda_p::tokens::complex_identifier *> (tokens.tokens [0]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_9 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.push_back (L'a');
	str.push_back (L'\0');
	str.push_back (L'a');
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 2);
	assert (dynamic_cast < ::lambda_p::tokens::identifier *> (tokens.tokens [0]) != NULL);
	assert (dynamic_cast < ::lambda_p::tokens::identifier *> (tokens.tokens [1]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_10 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.push_back (L'\0');
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_11 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";\"a;ba");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 1);
	assert (dynamic_cast < ::lambda_p::tokens::complex_identifier *> (tokens.tokens [0]) != NULL);
}

void lambda_p_test::simple_lexer_test_1::run_12 ()
{
	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";\"abc;");
	str.push_back ('a');
	str.push_back ('\t');
	str.push_back ('b');
	str.push_back ('\0');
	str.push_back ('c');
	str.append (L"abc");
	stream << str;
	stream.seekg (0);
	token_vector tokens;
	::lambda_p::serialization::simple_lexer < ::std::wstringstream, token_vector> parser (stream, tokens);
	parser.lex ();
	assert (tokens.tokens.size () == 1);
	assert (dynamic_cast < ::lambda_p::tokens::complex_identifier *> (tokens.tokens [0]) != NULL);
}