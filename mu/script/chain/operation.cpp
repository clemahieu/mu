#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/bool_c/node.h>

void mu::script::chain::operation::perform (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::script::operation> (context_a.parameters [0]));
		if (one.get () != nullptr)
		{
			std::vector <boost::shared_ptr <mu::core::node>> arguments (context_a.parameters.begin () + 1, context_a.parameters.end ());
			bool end (false);
			while (!end)
			{
				std::vector <boost::shared_ptr <mu::core::node>> results_l;
                auto ctx (mu::script::context (context_a.errors, arguments, results_l));
				one->perform (ctx);
				if (results_l.size () > 0)
				{
					auto val (boost::dynamic_pointer_cast <mu::script::bool_c::node> (results_l [results_l.size () - 1]));
					if (val.get () != nullptr)
					{
						end = val->value;
						arguments.swap (results_l);
						arguments.resize (arguments.size () - 1);
					}
					else
					{
						end = true;
						(*context_a.errors) (L"Last result must be a bool");
					}
				}
				else
				{
					end = true;
					(*context_a.errors) (L"Chain operation must have at least one result");
				}
			}
			context_a.results.insert (context_a.results.end (), arguments.begin (), arguments.end ());
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [0], 0);
		}
	}
	else
	{
		(*context_a.errors) (L"Chain operation must have at least one argument");
	}
}

std::wstring mu::script::chain::operation::name ()
{
	return std::wstring (L"mu::script::chain::operation");
}