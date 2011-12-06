#include "expression_leaf_iterator.h"

#include <lambda_p/core/expression_leaf.h>

#include <assert.h>

void lambda_p::core::expression_leaf_iterator::operator ++ ()
{
	assert (!end);
	end = true;
}

bool lambda_p::core::expression_leaf_iterator::operator == (lambda_p::core::expression_iterator_internal * other)
{
	bool result (false);
	auto o (dynamic_cast <lambda_p::core::expression_leaf_iterator *> (other));
	if (o != nullptr)
	{
		result = expression == o->expression && end == o->end;
	}

	return result;
}

bool lambda_p::core::expression_leaf_iterator::operator != (lambda_p::core::expression_iterator_internal * other)
{
	return ! operator == (other);
}

lambda_p::core::expression * lambda_p::core::expression_leaf_iterator::operator * ()
{
	assert (!end);
	return expression;
}