#include "node.h"

#include <lambda_p/core/node_iterator.h>

lambda_p::core::expression_iterator lambda_p::core::node::begin ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::node_iterator (this, false));
}

lambda_p::core::expression_iterator lambda_p::core::node::end ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::node_iterator (this, true));
}

bool lambda_p::core::node::resolved ()
{
	return true;
}