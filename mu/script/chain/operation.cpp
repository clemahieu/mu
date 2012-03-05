#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/bool_c/node.h>

void mu::script::chain::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::script::operation> (parameters [0]));
		if (one.get () != nullptr)
		{
			std::vector <boost::shared_ptr <mu::core::node>> arguments (parameters.begin () + 1, parameters.end ());
			bool end (false);
			while (!end)
			{
				std::vector <boost::shared_ptr <mu::core::node>> results_l;
				one->perform (errors_a, arguments, results_l);
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
						(*errors_a) (L"Last result must be a bool");
					}
				}
				else
				{
					end = true;
					(*errors_a) (L"Chain operation must have at least one result");
				}
			}
			results.insert (results.end (), arguments.begin (), arguments.end ());
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		(*errors_a) (L"Chain operation must have at least one argument");
	}
}

std::wstring mu::script::chain::operation::name ()
{
	return std::wstring (L"mu::script::chain::operation");
}