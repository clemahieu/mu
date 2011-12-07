#include "expression_leaf_iterator.h"

#include <lambda_p/core/expression.h>

#include <assert.h>

lambda_p::core::expression_leaf_iterator::expression_leaf_iterator (lambda_p::core::expression * expression_a, bool end_a)
	: expression (expression_a),
	end (end_a)
{
}

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