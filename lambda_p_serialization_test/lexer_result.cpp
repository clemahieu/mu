#include "lexer_result.h"

void lambda_p_serialization_test::lexer_result::operator () (lambda_p_serialization::tokens::token * token_a)
{
	results.push_back (token_a);
}