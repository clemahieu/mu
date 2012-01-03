#include "token_vector.h"

#include <lambda_p_serialization/tokens/token.h>

lambda_p_serialization::lexer::token_vector::token_vector(void)
	: tokens (new std::vector <lambda_p_serialization::tokens::token *>)
{
}

void lambda_p_serialization::lexer::token_vector::operator() (lambda_p_serialization::tokens::token * token)
{
	tokens->push_back (token);
}