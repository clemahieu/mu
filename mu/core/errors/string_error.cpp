#include <mu/core/errors/string_error.h>

#include <string>

mu::core::errors::string_error::string_error (std::wstring message_a)
	: message (message_a)
{
}

void mu::core::errors::string_error::string (std::wostream & stream) 
{
	stream << message;
}