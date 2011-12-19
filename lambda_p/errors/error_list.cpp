#include "error_list.h"

#include <lambda_p/errors/error.h>
#include <lambda_p/errors/string_error.h>

void lambda_p::errors::error_list::operator () (boost::shared_ptr <lambda_p::errors::error> error)
{
	errors.push_back (error);
}

void lambda_p::errors::error_list::operator () (lambda_p::errors::error * error)
{
	errors.push_back (boost::shared_ptr <lambda_p::errors::error> (error));
}

bool lambda_p::errors::error_list::operator() ()
{
	return !errors.empty ();
}

void lambda_p::errors::error_list::operator () (std::wstring & string_a)
{
	operator () (new lambda_p::errors::string_error (string_a));
}

void lambda_p::errors::error_list::operator () (wchar_t const * error)
{
	operator () (std::wstring (error));
}