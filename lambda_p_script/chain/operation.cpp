#include "operation.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/bool_c/node.h>

void lambda_p_script::chain::operation::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::operation> (parameters [0]));
	if (one.get () != nullptr)
	{
		std::vector <boost::shared_ptr <lambda_p::node>> arguments (parameters.begin () + 1, parameters.end ());
		bool end (false);
		while (!end)
		{
			std::vector <boost::shared_ptr <lambda_p::node>> results_l;
			one->perform (errors_a, arguments, results_l);
			if (results.size () > 0)
			{
				auto val (boost::dynamic_pointer_cast <lambda_p_script::bool_c::node> (results_l [results_l.size () - 1]));
				if (val.get () != nullptr)
				{
					end = val->value;
					arguments.swap (results_l);
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

std::wstring lambda_p_script::chain::operation::name ()
{
	return std::wstring (L"lambda_p_script::chain::operation");
}