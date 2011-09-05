#include "simple_parser_test_1.h"

#include <lambda_p/serialization/simple_parser.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/serialization/parse_result.h>

#include <vector>

lambda_p_test::simple_parser_test_1::simple_parser_test_1(void)
{
}

lambda_p_test::simple_parser_test_1::~simple_parser_test_1(void)
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

struct routine_vector
{
	void operator () (::lambda_p::serialization::parse_result result)
	{
		routines.push_back (result);
	}
	::std::vector < ::lambda_p::serialization::parse_result> routines;
};

void lambda_p_test::simple_parser_test_1::run ()
{
	run_1 ();
}

void lambda_p_test::simple_parser_test_1::run_1 ()
{
	token_vector tokens;
	routine_vector routines;
	::std::vector < ::lambda_p::tokens::token *>::iterator begin = tokens.tokens.begin ();
	::std::vector < ::lambda_p::tokens::token *>::iterator end = tokens.tokens.end ();
	::lambda_p::serialization::simple_parser < ::std::vector < ::lambda_p::tokens::token *>::iterator, routine_vector> parser (begin, end, routines);
	parser.parse ();
}
