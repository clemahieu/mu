#include "analyzer_result.h"

void lambda_p_serialization_test::analyzer_result::operator () (boost::shared_ptr <lambda_p::core::routine> routine_a)
{
	routines.push_back (routine_a);
}

void lambda_p_serialization_test::analyzer_result::operator () (boost::shared_ptr <lambda_p::errors::error> error_a)
{
	errors.push_back (error_a);
}