#include "expression_iterator.h"

#include <lambda_p/core/expression_iterator_internal.h>

lambda_p::core::expression_iterator::expression_iterator ()
{
}

lambda_p::core::expression_iterator::expression_iterator (lambda_p::core::expression_iterator_internal * iter_a)
	: iter (iter_a)
{
}

void lambda_p::core::expression_iterator::operator ++ ()
{
	iter->operator++ ();
}

bool lambda_p::core::expression_iterator::operator == (lambda_p::core::expression_iterator & other)
{
	return iter->operator== (other.iter);
}

bool lambda_p::core::expression_iterator::operator != (lambda_p::core::expression_iterator & other)
{
	return iter->operator!= (other.iter);
}

lambda_p::core::expression * lambda_p::core::expression_iterator::operator * ()
{
	return iter->operator* ();
}