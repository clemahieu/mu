#include <lambda_p_io/parser/error.h>

lambda_p_io::parser::error::error (std::wstring message_a)
	: message (message_a)
{
}

void lambda_p_io::parser::error::operator () (lambda_p_io::tokens::divider * token)
{
}

void lambda_p_io::parser::error::operator () (lambda_p_io::tokens::identifier * token)
{
}

void lambda_p_io::parser::error::operator () (lambda_p_io::tokens::left_square * token)
{
}

void lambda_p_io::parser::error::operator () (lambda_p_io::tokens::right_square * token)
{
}

void lambda_p_io::parser::error::operator () (lambda_p_io::tokens::stream_end * token)
{
}