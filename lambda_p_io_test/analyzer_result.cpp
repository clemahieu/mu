#include "analyzer_result.h"

#include <lambda_p/errors/error_list.h>

lambda_p_io_test::analyzer_result::analyzer_result ()
	: errors (new lambda_p::errors::error_list)
{
}

void lambda_p_io_test::analyzer_result::operator () (boost::shared_ptr <lambda_p::core::routine> routine_a)
{
	routines.push_back (routine_a);
}