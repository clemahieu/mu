#include "expression_list.h"

#include <lambda_p/core/expression_list_iterator.h>

lambda_p::core::expression_iterator lambda_p::core::expression_list::begin ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::expression_list_iterator (*this));
}

lambda_p::core::expression_iterator lambda_p::core::expression_list::end ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::expression_list_iterator (*this));
}