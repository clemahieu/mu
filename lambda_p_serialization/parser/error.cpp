#include <lambda_p/parser/error.h>

lambda_p::parser::error::error(std::wstring message_a)
	: message (message_a)
{
}

void lambda_p::parser::error::parse (lambda_p::tokens::token * token)
{
}