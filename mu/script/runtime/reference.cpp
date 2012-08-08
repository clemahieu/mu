#include <mu/script/runtime/reference.h>

#include <mu/script/context.h>
#include <mu/script/runtime/locals.h>
#include <mu/core/check.h>
#include <mu/core/errors/error_target.h>

#include <sstream>

mu::script::runtime::reference::reference (mu::script::runtime::expression * expression_a)
	: expression (expression_a)
{
}

bool mu::script::runtime::reference::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::script::runtime::locals> (context_a));
	if (valid)
	{
		auto locals (static_cast <mu::script::runtime::locals *> (context_a.parameters (0)));
		auto existing (locals->expressions.find (expression));
		if (existing != locals->expressions.end ())
		{
			if (existing->second.get <1> () <= locals->frame.size ())
			{
				context_a.push (locals->frame.begin () + existing->second.get <0> (), locals->frame.begin () + existing->second.get <1> ());
			}
			else
			{
				if (existing->second.get <1> () != ~0)
				{
					mu::stringstream message;
					message << L"Trying to get values off of frame from: ";
					message << existing->second.get <0> ();
					message << L" to: ";
					message << existing->second.get <1> ();
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