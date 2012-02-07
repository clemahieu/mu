#include "operation.h"

lambda_p_script::values::operation::operation (std::vector <boost::shared_ptr <lambda_p::node>> values_a)
	: values (values_a)
{
}

void lambda_p_script::values::operation::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	results.insert (results.end (), values.begin (), values.end ());
}

size_t lambda_p_script::values::operation::count ()
{
	return 0 ;
}