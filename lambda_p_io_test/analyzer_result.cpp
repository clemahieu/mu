#include "analyzer_result.h"

#include <core/errors/error_list.h>

lambda_p_io_test::analyzer_result::analyzer_result ()
	: errors (new mu::core::errors::error_list)
{
}

void lambda_p_io_test::analyzer_result::operator () (boost::shared_ptr <mu::core::cluster> cluster_a)
{
	clusters.push_back (cluster_a);
}