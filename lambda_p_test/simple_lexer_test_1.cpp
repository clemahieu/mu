#include "simple_lexer_test_1.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/serialization/lexer/simple_lexer.h>
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
	token_vector (::std::vector < ::lambda_p::tokens::token *> & tokens_a)
		: tokens (tokens_a)
	{
	}
	void operator () (::lambda_p::tokens::token * token)
	{
		tokens.push_back (token);
	}
	::std::vector < ::lambda_p::tokens::token *> & tokens;
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
	run_13 ();
}

void lambda_p_test::simple_lexer_test_1::run_1 ()
{
	::std::wstringstream stream;
	::lambda_p::core::routine routine (0);
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (stream);
	serializer.routine (&routine);
	::std::wstring str (stream.str ());
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 3);
	assert (tokens [0]->token_id () == ::lambda_p::tokens::token_id_identifier);
	assert (tokens [1]->token_id () == ::lambda_p::tokens::token_id_statement_end);
	assert (tokens [2]->token_id () == ::lambda_p::tokens::token_id_routine_end);
}

void lambda_p_test::simple_lexer_test_1::run_2 ()
{
	::std::wstring str;
	str.append (L"routine0033F838\n");
	str.append (L";/junk12346680!@#$%^&*();astnhcheou\n");
	str.append (L";;\n");
	str.append (L";.\n");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 3);
	assert (tokens [0]->token_id () == ::lambda_p::tokens::token_id_identifier);
	assert (tokens [1]->token_id () == ::lambda_p::tokens::token_id_statement_end);
	assert (tokens [2]->token_id () == ::lambda_p::tokens::token_id_routine_end);
}

void lambda_p_test::simple_lexer_test_1::run_3 ()
{
	::std::wstring str;
	str.append (L";/");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_4 ()
{
	::std::wstring str;
	str.append (L";*;*");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_5 ()
{
	::std::wstring str;
	str.append (L";*");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (lexer.error ());
	assert (tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_6 ()
{
	::std::wstring str;
	str.append (L";*;");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (lexer.error ());
	assert (tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_7 ()
{
	::std::wstring str;
	str.append (L";\"");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (lexer.error ());
	assert (tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_8 ()
{	::std::wstringstream stream;
	::std::wstring str;
	str.append (L";\";");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 1);
	assert (tokens [0]->token_id () == ::lambda_p::tokens::token_id_complex_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_9 ()
{
	::std::wstring str;
	str.push_back (L'a');
	str.push_back (L'\0');
	str.push_back (L'a');
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (tokens.size () == 2);
	assert (tokens [0]->token_id () == ::lambda_p::tokens::token_id_identifier);
	assert (tokens [1]->token_id () == ::lambda_p::tokens::token_id_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_10 ()
{
	::std::wstring str;
	str.push_back (L'\0');
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 0);
}

void lambda_p_test::simple_lexer_test_1::run_11 ()
{
	::std::wstring str;
	str.append (L";\"a;ba");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 1);
	assert (tokens [0]->token_id () == ::lambda_p::tokens::token_id_complex_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_12 ()
{
	::std::wstring str;
	str.append (L";\"abc;");
	str.push_back ('a');
	str.push_back ('\t');
	str.push_back ('b');
	str.push_back ('\0');
	str.push_back ('c');
	str.append (L"abc");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 1);
	assert (tokens [0]->token_id () == ::lambda_p::tokens::token_id_complex_identifier);
}

void lambda_p_test::simple_lexer_test_1::run_13 ()
{
	::std::wstring str;
	str.append (L"routine1;; ");
	::std::vector < ::lambda_p::tokens::token *> tokens;
	token_vector holder (tokens);
	::boost::function <void (::lambda_p::tokens::token *)> target (holder);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	for (::std::wstring::iterator i = str.begin (); i != str.end (); ++i)
	{
		lexer (*i);
	}
	lexer.end ();
	assert (!lexer.error ());
	assert (tokens.size () == 2);
	assert (tokens [0]->token_id () == ::lambda_p::tokens::token_id_identifier);
	assert (tokens [1]->token_id () == ::lambda_p::tokens::token_id_statement_end);
}