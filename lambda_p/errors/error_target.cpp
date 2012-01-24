#include "error_target.h"

#include <lambda_p/errors/string_error.h>

void lambda_p::errors::error_target::operator () (std::wstring error)
{
	(*this) (error, lambda_p::context ());
}

void lambda_p::errors::error_target::operator () (wchar_t const * error)
{
	(*this) (error, lambda_p::context ());
}

void lambda_p::errors::error_target::operator () (std::wstring error, lambda_p::context context_a)
{
	(*this) (boost::shared_ptr <lambda_p::errors::string_error> (new lambda_p::errors::string_error (error)), context_a);
}

void lambda_p::errors::error_target::operator () (wchar_t const * error, lambda_p::context context_a)
{
	(*this) (std::wstring (error), context_a);
}