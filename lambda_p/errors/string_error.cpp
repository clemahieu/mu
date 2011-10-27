#include "string_error.h"

#include <string>

lambda_p::errors::string_error::string_error (std::wstring message_a)
	: message (message_a)
{
}

lambda_p::errors::error_id lambda_p::errors::string_error::error_type ()
{
	return lambda_p::errors::error_string_error;
}

void lambda_p::errors::string_error::string (std::wostream & stream) 
{
	stream << message;
}