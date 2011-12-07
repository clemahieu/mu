#include "expression_list_iterator.h"

#include <lambda_p/core/expression.h>
#include <lambda_p/core/expression_leaf_iterator.h>

#include <assert.h>

lambda_p::core::expression_list_iterator::expression_list_iterator (lambda_p::core::expression_iterator target_current_a, lambda_p::core::expression_iterator target_end_a, std::vector <lambda_p::core::expression *>::iterator current_a, std::vector <lambda_p::core::expression *>::iterator end_a)
	: current (current_a),
	end (end_a),
	target_current (target_current_a),
	target_end (target_end_a)
{
}

void lambda_p::core::expression_list_iterator::operator ++ ()
{
	assert (current != end);
	assert (target_current != target_end);
	++target_current;
	if (target_current == target_end)
	{
		++current;
		if (current != end)
		{
			target_current = (*current)->begin ();
			target_end = (*current)->end ();
		}
		else
		{
			target_current = lambda_p::core::expression_iterator (new lambda_p::core::expression_leaf_iterator (nullptr, true));
			target_end = lambda_p::core::expression_iterator (new lambda_p::core::expression_leaf_iterator (nullptr, true));
		}
	}
}

bool lambda_p::core::expression_list_iterator::operator == (lambda_p::core::expression_iterator_internal * other)
{
	bool result (false);
	auto o (dynamic_cast <lambda_p::core::expression_list_iterator *> (other));
	if (o != nullptr)
	{
		result = current == o->current && target_current == o->target_current;
	}

	return result;
}

bool lambda_p::core::expression_list_iterator::operator != (lambda_p::core::expression_iterator_internal * other)
{
	return ! operator == (other);
}

lambda_p::core::expression * lambda_p::core::expression_list_iterator::operator * ()
{
	assert (current != end);
	return *current;
}