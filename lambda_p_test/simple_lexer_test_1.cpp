#include "simple_lexer_test_1.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/lexer/simple_lexer.h>
#include <lambda_p/tokens/token.h>
#include <lambda_p/serialization/simple.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/lexer/token_vector.h>

#include <boost/bind.hpp>

#include <sstream>

lambda_p_test::simple_lexer_test_1::simple_lexer_test_1(void)
{
}

lambda_p_test::simple_lexer_test_1::~simple_lexer_test_1(void)
{
}

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
	run_13 ();
}

void lambda_p_test::simple_lexer_test_1::run_1 ()
{
	::std::wstringstream stream;
	::lambda_p::core::routine routine;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (stream);
	serializer.routine (&routine);
	::std::wstring str (stream.str ());
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 3);
	assert ((*tokens.tokens) [0]->token_id () == ::lambda_p::tokens::token_id_connector);
	assert ((*tokens.tokens) [1]->token_id () == ::lambda_p::tokens::token_id_statement_end);
	assert ((*tokens.tokens) [2]->token_id () == ::lambda_p::tokens::token_id_routine_end);
}

void lambda_p_test::simple_lexer_test_1::run_2 ()
{
	::std::wstring str;
	str.append (L"routine0033F838\n");
	str.append (L"#/junk12346680!@#$%^&*();astnhcheou\n");
	str.append (L";\n");
	str.append (L"#;\n");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 3);
	assert ((*tokens.tokens) [0]->token_id () == ::lambda_p::tokens::token_id_identifier);
	assert ((*tokens.tokens) [1]->token_id () == ::lambda_p::tokens::token_id_statement_end);
	assert ((*tokens.tokens) [2]->token_id () == ::lambda_p::tokens::token_id_routine_end);
}

void lambda_p_test::simple_lexer_test_1::run_3 ()
{
	::std::wstring str;
	str.append (L"#/");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (tokens.tokens->size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_4 ()
{
	::std::wstring str;
	str.append (L"#*#*");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_5 ()
{
	::std::wstring str;
	str.append (L"#*");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (lexer.error ());
	assert (tokens.tokens->size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_6 ()
{
	::std::wstring str;
	str.append (L"#*");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (lexer.error ());
	assert (tokens.tokens->size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_7 ()
{
	::std::wstring str;
	str.append (L"\"");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (lexer.error ());
	assert (tokens.tokens->size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_8 ()
{	::std::wstringstream stream;
	::std::wstring str;
	str.append (L"\"\"");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 1);
	assert ((*tokens.tokens) [0]->token_id () == ::lambda_p::tokens::token_id_complex_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_9 ()
{
	::std::wstring str;
	str.push_back (L'a');
	str.push_back (L'\0');
	str.push_back (L'a');
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (tokens.tokens->size () == 2);
	assert ((*tokens.tokens) [0]->token_id () == ::lambda_p::tokens::token_id_identifier);
	assert ((*tokens.tokens) [1]->token_id () == ::lambda_p::tokens::token_id_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_10 ()
{
	::std::wstring str;
	str.push_back (L'\0');
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_11 ()
{
	::std::wstring str;
	str.append (L"\"a\"ba");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 1);
	assert ((*tokens.tokens) [0]->token_id () == ::lambda_p::tokens::token_id_complex_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_12 ()
{
	::std::wstring str;
	str.append (L"\"abc\"");
	str.push_back ('a');
	str.push_back ('\t');
	str.push_back ('b');
	str.push_back ('\0');
	str.push_back ('c');
	str.append (L"abc");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 1);
	assert ((*tokens.tokens) [0]->token_id () == ::lambda_p::tokens::token_id_complex_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_13 ()
{
	::std::wstring str;
	str.append (L"routine1; ");
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::lexer::simple_lexer lexer (::boost::bind <void> (tokens, _1));
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer (L'\uee0f');
	assert (!lexer.error ());
	assert (tokens.tokens->size () == 2);
	assert ((*tokens.tokens) [0]->token_id () == ::lambda_p::tokens::token_id_identifier);
	assert ((*tokens.tokens) [1]->token_id () == ::lambda_p::tokens::token_id_statement_end);
}