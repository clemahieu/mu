#include "simple_parser_test_1.h"

#include <lambda_p/serialization/parser/simple_parser.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/serialization/parser/parse_result.h>

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
	void operator () (::lambda_p::serialization::parser::parse_result result)
	{
		routines.push_back (result);
	}
	::std::vector < ::lambda_p::serialization::parser::parse_result> routines;
};

void lambda_p_test::simple_parser_test_1::run ()
{
	run_1 ();
}

void lambda_p_test::simple_parser_test_1::run_1 ()
{
	token_vector tokens;
	routine_vector routines;
	::lambda_p::serialization::simple_parser <routine_vector> parser (routines);
	parser (NULL);
}
