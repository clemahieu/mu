#include "analyzer_result.h"

#include <lambda_p/errors/error_list.h>

lambda_p_io_test::analyzer_result::analyzer_result ()
	: errors (new lambda_p::errors::error_list)
{
}

void lambda_p_io_test::analyzer_result::operator () (boost::shared_ptr <lambda_p::cluster> cluster_a)
{
	clusters.push_back (cluster_a);
}