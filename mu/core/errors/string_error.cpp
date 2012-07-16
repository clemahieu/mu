#include <mu/core/errors/string_error.h>

#include <string>

mu::core::errors::string_error::string_error (mu::string message_a)
	: message (message_a)
{
}

void mu::core::errors::string_error::string (mu::ostream & stream) 
{
	stream << message;
}