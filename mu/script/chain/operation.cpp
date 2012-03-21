#include <mu/script/chain/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

bool mu::script::chain::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::script::operation> (context_a.parameters (0)));
		if (one.get () != nullptr)
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
						auto val (boost::dynamic_pointer_cast <mu::script::bool_c::node> (context_a.working (context_a.working_size () - 1)));
						if (val.get () != nullptr)
						{
							end = val->value;
							context_a.assign (context_a.locals_begin (), context_a.working_begin (), context_a.working_end () - 1);
							context_a.drop ();
						}
						else
						{
							context_a.errors (L"Last result must be a bool");
							result = false;
						}
					}
					else
					{
						context_a.errors (L"Chain operation must have at least one result");
						result = false;
					}
				}
			}
			context_a.push (context_a.locals_begin (), context_a.locals_end ());
		}
		else
		{
			mu::script::invalid_type (context_a, typeid (*context_a.parameters (0).get ()), typeid (mu::script::operation), 0);
			result = false;
		}
	}
	else
	{
		context_a.errors (L"Chain operation must have at least one argument");
		result = false;
	}
	return result;
}

std::wstring mu::script::chain::operation::name ()
{
	return std::wstring (L"mu::script::chain::operation");
}