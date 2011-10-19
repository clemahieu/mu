#include "token_vector.h"

#include <lambda_p/tokens/token.h>

lambda_p::lexer::token_vector::token_vector(void)
	: tokens (new std::vector < lambda_p::tokens::token *>)
{
}

lambda_p::lexer::token_vector::~token_vector(void)
{
}

void lambda_p::lexer::token_vector::operator() (lambda_p::tokens::token * token)
{
	tokens->push_back (token);
}