#include "expression_list_iterator.h"

#include <lambda_p/core/expression_list.h>

#include <assert.h>

lambda_p::core::expression_list_iterator::expression_list_iterator (lambda_p::core::expression_list & list_a)
	: current (list_a.contents.begin ()),
	end (list_a.contents.end ())
{
}

void lambda_p::core::expression_list_iterator::operator ++ ()
{
	assert (current != end);
	++current;
}

bool lambda_p::core::expression_list_iterator::operator == (lambda_p::core::expression_iterator_internal * other)
{
	bool result (false);
	auto o (dynamic_cast <lambda_p::core::expression_list_iterator *> (other));
	if (o != nullptr)
	{
		result = current == end;
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