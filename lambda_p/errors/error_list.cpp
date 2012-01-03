#include "error_list.h"

void lambda_p::errors::error_list::operator () (boost::shared_ptr <lambda_p::errors::error> error)
{
	errors.push_back (error);
}

bool lambda_p::errors::error_list::operator () ()
{
	return !errors.empty ();
}