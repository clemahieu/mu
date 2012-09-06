#include <mu/script/chain_operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/bool_c_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

bool mu::script::chain::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto one (dynamic_cast <mu::script::operation *> (context_a.parameters (0)));
		if (one != nullptr)
		{
			context_a.reserve (context_a.parameters_size () - 1);
			context_a.assign (context_a.locals_begin (), context_a.parameters_begin () + 1, context_a.parameters_end ());
			bool end (false);
			while (result && !end)
			{
				context_a.push (one);
				context_a.push (context_a.locals_begin (), context_a.locals_end ());
				result = context_a ();
				if (result)
				{
					if (context_a.working_size () > 0)
					{
						auto val (dynamic_cast <mu::script::bool_c::node *> (context_a.working (context_a.working_size () - 1)));
						if (val != nullptr)
						{
							end = val->value;
							context_a.assign (context_a.locals_begin (), context_a.working_begin (), context_a.working_end () - 1);
							context_a.drop ();
						}
						else
						{
							context_a.errors (U"Last result must be a booU");
							result = false;
						}
					}
					else
					{
						context_a.errors (U"Chain operation must have at least one result");
						result = false;
					}
				}
			}
			context_a.push (context_a.locals_begin (), context_a.locals_end ());
		}
		else
		{
			mu::core::type_fail(context_a.errors, typeid (mu::script::operation), context_a.parameters (0), 0);
			result = false;
		}
	}
	else
	{
		context_a.errors (U"Chain operation must have at least one argument");
		result = false;
	}
	return result;
}

mu::string mu::script::chain::operation::name ()
{
	return mu::string (U"mu::script::chain::operation");
}