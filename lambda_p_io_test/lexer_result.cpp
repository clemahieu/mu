#include "lexer_result.h"

void lambda_p_io_test::lexer_result::operator () (lambda_p_io::tokens::token * token_a)
{
	results.push_back (token_a);
}