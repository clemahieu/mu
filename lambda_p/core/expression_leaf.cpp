#include "expression_leaf.h"

#include <lambda_p/core/expression_leaf_iterator.h>

lambda_p::core::expression_iterator lambda_p::core::expression_leaf::begin ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::expression_leaf_iterator (this, false));
}

lambda_p::core::expression_iterator lambda_p::core::expression_leaf::end ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::expression_leaf_iterator (this, true));
}