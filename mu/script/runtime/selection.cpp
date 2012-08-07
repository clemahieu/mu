#include <mu/script/runtime/selection.h>

#include <mu/script/check.h>
#include <mu/script/runtime/locals.h>
#include <mu/core/errors/error_target.h>

#include <sstream>

mu::script::runtime::selection::selection (mu::script::runtime::expression * expression_a, size_t index_a)
	: expression (expression_a),
    index (index_a)	
{
}

bool mu::script::runtime::selection::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::script::runtime::locals> (context_a));
	if (valid)
	{
		auto locals (static_cast <mu::script::runtime::locals *> (context_a.parameters (0)));
		auto existing (locals->expressions.find (expression));
		if (existing != locals->expressions.end ())
		{
			if (existing->second.get <0> () + index < locals->frame.size ())
			{
				if (existing->second.get <0> () + index < existing->second.get <1> ())
				{
					context_a.push (*(locals->frame.begin () + existing->second.get <0> () + index));
				}
				else
				{
					mu::stringstream message;
					message << L"Trying to get result at index: ";
					message << index;
					message << L" but there are only: ";
					message << existing->second.get <1> () - existing->second.get <0> ();
					message << L" nodes";
					context_a.errors (message.str ());
					valid = false;
				}
			}
			else
			{
				if (existing->second.get <1> () != ~0)
				{
					mu::stringstream message;
					message << L"Trying to select value off of frame at: ";
					message << existing->second.get <0> () + index;
					message << L" but only have: ";
					message << locals->frame.size ();
					context_a.errors (message.str ());
				}
				else
				{
					// Poisoned arguments aren't an error condition of *this* reference
				}
				valid = false;
			}
		}
		else
		{
			context_a.errors (U"Expression is not mapped");
			valid = false;
		}
	}
	return valid;
}