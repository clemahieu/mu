#include "lexer_result.h"

void lambda_p_io_test::lexer_result::operator () (lambda_p_io::tokens::token * token_a, mu::core::context context_a)
{
	results.push_back (std::pair <lambda_p_io::tokens::token *, mu::core::context> (token_a, context_a));
}