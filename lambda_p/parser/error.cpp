#include <lambda_p/parser/error.h>

lambda_p::parser::error::error(::std::wstring message_a)
	: message (message_a)
{
}

lambda_p::parser::error::~error(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::error::state_type ()
{
	return lambda_p::parser::state_error;
}
