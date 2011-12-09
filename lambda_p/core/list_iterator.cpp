#include "list_iterator.h"

#include <lambda_p/core/expression.h>
#include <lambda_p/core/list.h>

#include <assert.h>

lambda_p::core::list_iterator::list_iterator ()
{
}

lambda_p::core::list_iterator::list_iterator (boost::shared_ptr <lambda_p::core::list> list_a, bool end_a)
	: list (list_a),
	current (end_a ? list_a->contents.end () : list_a->contents.begin ()),
	end (list_a->contents.end ())
{
	set_target ();
	skip ();
}

void lambda_p::core::list_iterator::set_target ()
{
	if (current != end)
	{
		auto current_l (boost::dynamic_pointer_cast <lambda_p::core::list> (*current));
		if (current_l.get () != nullptr)
		{
			target_current.reset (new lambda_p::core::list_iterator (current_l, false));
			target_end.reset (new lambda_p::core::list_iterator (current_l, true));
		}
		else
		{
			target_current.reset ();
			target_end.reset ();
		}
	}
	else
	{
		target_current.reset ();
		target_current.reset ();
	}
}

void lambda_p::core::list_iterator::skip ()
{
	boost::shared_ptr <lambda_p::core::list> current_l;
	while (current != end && (current_l = boost::dynamic_pointer_cast <lambda_p::core::list> (*current)).get () != nullptr && *target_current == *target_end)
	{
		++current;
		set_target ();
	}
}

void lambda_p::core::list_iterator::operator ++ ()
{
	assert (current != end);
	auto current_l (boost::dynamic_pointer_cast <lambda_p::core::list> (*current));
	if (current_l.get () != nullptr)
	{
		++*target_current;
	}
	else
	{
		++current;
		set_target ();
	}
	skip ();
}

bool lambda_p::core::list_iterator::operator == (lambda_p::core::list_iterator const & other)
{
	bool result (current == other.current);
	result = result && target_current.get () == other.target_current.get ();
	if (target_current.get () != nullptr)
	{
		result = result && *target_current == *other.target_current;
	}
	return result;
}

bool lambda_p::core::list_iterator::operator != (lambda_p::core::list_iterator const & other)
{
	return ! operator == (other);
}

boost::shared_ptr <lambda_p::core::expression> lambda_p::core::list_iterator::operator * ()
{
	assert (current != end);
	boost::shared_ptr <lambda_p::core::expression> result;
	auto current_l (boost::dynamic_pointer_cast <lambda_p::core::list> (*current));
	if (current_l.get () != nullptr)
	{
		result = **target_current;
	}
	else
	{
		result = current_l;
	}
	return result;
}