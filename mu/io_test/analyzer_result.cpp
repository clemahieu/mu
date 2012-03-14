#include <mu/io_test/analyzer_result.h>

#include <mu/core/errors/error_list.h>

mu::io_test::analyzer_result::analyzer_result ()
	: errors (new mu::core::errors::error_list)
{
}

void mu::io_test::analyzer_result::operator () (boost::shared_ptr <mu::core::cluster> cluster_a, boost::shared_ptr <mu::io::debugging::mapping> cluster_info_a)
{
	clusters.push_back (cluster_a);
	mappings.push_back (cluster_info_a);
}