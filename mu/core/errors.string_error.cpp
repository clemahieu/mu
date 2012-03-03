#include "errors.string_error.h"

#include <string>

mu::core::errors::string_error::string_error (std::wstring message_a)
	: message (message_a)
{
}

mu::core::errors::error_id mu::core::errors::string_error::error_type ()
{
	return mu::core::errors::error_string_error;
}

void mu::core::errors::string_error::string (std::wostream & stream) 
{
	stream << message;
}
