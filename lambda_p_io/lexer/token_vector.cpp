#include "token_vector.h"

#include <lambda_p_io/tokens/token.h>

lambda_p_io::lexer::token_vector::token_vector(void)
	: tokens (new std::vector <lambda_p_io::tokens::token *>)
{
}

void lambda_p_io::lexer::token_vector::operator() (lambda_p_io::tokens::token * token)
{
	tokens->push_back (token);
}