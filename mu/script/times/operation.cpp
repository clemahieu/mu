#include <mu/script/times/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/integer/node.h>
#include <mu/script/check.h>

#include <sstream>

bool mu::script::times::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 1)
	{
		auto one (dynamic_cast <mu::script::integer::node *> (context_a.parameters (0)));
		auto two (dynamic_cast <mu::core::node *> (context_a.parameters (1)));
		if (one != nullptr)
		{
			if (two != nullptr)
			{
				context_a.reserve (context_a.parameters_size () - 2);
				context_a.assign (context_a.locals_begin (), context_a.parameters_begin () + 2, context_a.parameters_end ());
				for (size_t i (0), j (one->value); i != j && result; ++i)
				{
					context_a.push (two);
					context_a.push (context_a.locals_begin (), context_a.locals_end ());
					result = context_a ();
					result = result && context_a.locals_size () == context_a.working_size ();
					context_a.assign (context_a.locals_begin (), context_a.working_begin (), context_a.working_end ());
					context_a.drop ();
				}
				context_a.push (context_a.locals_begin (), context_a.locals_end ());
			}
			else
			{
				mu::script::invalid_type (context_a, context_a.parameters (1), typeid (mu::script::operation), 1);
				result = false;
			}
		}
		else
		{
			mu::script::invalid_type (context_a, context_a.parameters (0), typeid (mu::script::integer::node), 0);
			result = false;
		}
	}
	else
	{
		mu::stringstream message;
		message << name ();
		message << L" must have at least two arguments";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

mu::string mu::script::times::operation::name ()
{
	return mu::string (U"mu::script::times::operation");
}