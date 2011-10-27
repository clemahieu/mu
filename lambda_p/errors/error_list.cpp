#include "error_list.h"

#include <lambda_p/errors/error.h>

void lambda_p::errors::error_list::operator () (boost::shared_ptr <lambda_p::errors::error> error)
{
	errors.push_back (error);
}

void lambda_p::errors::error_list::operator () (lambda_p::errors::error * error)
{
	errors.push_back (boost::shared_ptr <lambda_p::errors::error> (error));
}