#include <lambda_p_serialization/parser/error.h>

lambda_p_serialization::parser::error::error (std::wstring message_a)
	: message (message_a)
{
}

void lambda_p_serialization::parser::error::operator () (lambda_p_serialization::tokens::divider * token)
{
}

void lambda_p_serialization::parser::error::operator () (lambda_p_serialization::tokens::identifier * token)
{
}

void lambda_p_serialization::parser::error::operator () (lambda_p_serialization::tokens::left_square * token)
{
}

void lambda_p_serialization::parser::error::operator () (lambda_p_serialization::tokens::right_square * token)
{
}

void lambda_p_serialization::parser::error::operator () (lambda_p_serialization::tokens::stream_end * token)
{
}