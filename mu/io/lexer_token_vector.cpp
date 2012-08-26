#include <mu/io/lexer_token_vector.h>

#include <mu/io/tokens_token.h>

mu::io::lexer::token_vector::token_vector(void)
	: tokens (new std::vector <mu::io::tokens::token *>)
{
}

void mu::io::lexer::token_vector::operator() (mu::io::tokens::token * token)
{
	tokens->push_back (token);
}