#include "node_iterator.h"

#include <lambda_p/core/node_iterator.h>
#include <lambda_p/core/node.h>

#include <assert.h>

void lambda_p_test::node_iterator::run ()
{
	run_1 ();
}

void lambda_p_test::node_iterator::run_1 ()
{
	auto node (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	lambda_p::core::node_iterator begin (node, false);
	lambda_p::core::node_iterator end (node, false);
	assert (begin != end);
	++begin;
	assert (begin == end);
}