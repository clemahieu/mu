#include <mu/test_entry/io/analyzer_result.h>

#include <mu/core/errors/error_list.h>

#include <gc_cpp.h>

mu::io_test::analyzer_result::analyzer_result ()
	: errors (new (GC) mu::core::errors::error_list)
{
}

void mu::io_test::analyzer_result::operator () (mu::core::cluster * cluster_a)
{
	clusters.push_back (cluster_a);
}