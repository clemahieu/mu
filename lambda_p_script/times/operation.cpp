#include "operation.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/integer/node.h>

#include <sstream>

void lambda_p_script::times::operation::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 1)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (parameters [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_script::operation> (parameters [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				std::vector <boost::shared_ptr <lambda_p::node>> results_l (parameters.begin () + 2, parameters.end ());
				for (size_t i (0), j (one->value); i != j; ++i)
				{
					std::vector <boost::shared_ptr <lambda_p::node>> arguments;
					arguments.swap (results_l);
					two->perform (errors_a, arguments, results_l);
				}
				results.insert (results.end (), results_l.begin (), results_l.end ());
			}
			else
			{
				invalid_type (errors_a, parameters [1], 1);
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" must have at least two arguments";
		(*errors_a) (message.str ());
	}
}

std::wstring lambda_p_script::times::operation::name ()
{
	return std::wstring (L"lambda_p_script::times::operation");
}