#include "list_iterator.h"

#include <lambda_p/core/expression.h>
#include <lambda_p/core/list.h>
#include <lambda_p/core/node_iterator.h>

#include <assert.h>

lambda_p::core::list_iterator::list_iterator (lambda_p::core::list & list_a, bool end_a)
{
	if (end_a)
	{
		current = list_a.contents.end ();
		end = list_a.contents.end ();
		target_current = lambda_p::core::expression_iterator (new lambda_p::core::node_iterator (nullptr, true));
		target_end = lambda_p::core::expression_iterator (new lambda_p::core::node_iterator (nullptr, true));
	}
	else
	{
		current = list_a.contents.begin ();
		end = list_a.contents.end ();
		if (current != end)
		{
			target_current = (*current)->begin ();
			target_end = (*current)->end ();
		}
		skip ();
	}
}

void lambda_p::core::list_iterator::check_end ()
{
	if (current == end)
	{
		target_current = lambda_p::core::expression_iterator (new lambda_p::core::node_iterator (nullptr, true));
		target_end = lambda_p::core::expression_iterator (new lambda_p::core::node_iterator (nullptr, true));
	}
}

void lambda_p::core::list_iterator::skip ()
{
	while (current != end && target_current == target_end)
	{
		++current;
		target_current = (*current)->begin ();
		target_end = (*current)->end ();
	}
	check_end ();
}

void lambda_p::core::list_iterator::operator ++ ()
{
	++target_current;
	skip ();
}

bool lambda_p::core::list_iterator::operator == (lambda_p::core::expression_iterator_internal * other)
{
	bool result (false);
	auto o (dynamic_cast <lambda_p::core::list_iterator *> (other));
	if (o != nullptr)
	{
		result = current == o->current && target_current == o->target_current;
	}

	return result;
}

bool lambda_p::core::list_iterator::operator != (lambda_p::core::expression_iterator_internal * other)
{
	return ! operator == (other);
}

boost::shared_ptr <lambda_p::core::expression> lambda_p::core::list_iterator::operator * ()
{
	assert (current != end);
	return *current;
}