#include <lambda_p_serialization/parser/error.h>

lambda_p_serialization::parser::error::error(std::wstring message_a)
	: message (message_a)
{
}

void lambda_p_serialization::parser::error::parse (lambda_p::tokens::token * token)
{
}