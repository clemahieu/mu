#include "error_target.h"

#include <lambda_p/errors/string_error.h>

void lambda_p::errors::error_target::operator () (std::wstring error)
{
	(*this) (boost::shared_ptr <lambda_p::errors::string_error> (new lambda_p::errors::string_error (error)));
}

void lambda_p::errors::error_target::operator () (wchar_t const * error)
{
	(*this) (std::wstring (error));
}