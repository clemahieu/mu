#include "error_list.h"

void lambda_p::errors::error_list::operator () (boost::shared_ptr <lambda_p::errors::error> error, lambda_p::context context_a)
{
	errors.push_back (std::pair <boost::shared_ptr <lambda_p::errors::error>, lambda_p::context> (error, context_a));
}

bool lambda_p::errors::error_list::operator () ()
{
	return !errors.empty ();
}