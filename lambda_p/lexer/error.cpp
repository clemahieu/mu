#include <lambda_p/lexer/error.h>

lambda_p::lexer::error::error (std::wstring message_a)
	: message (message_a)
{
}

lambda_p::lexer::error::~error (void)
{
}

lambda_p::lexer::state_id lambda_p::lexer::error::state_type ()
{
	return lambda_p::lexer::state_error;
}