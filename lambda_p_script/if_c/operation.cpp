#include "operation.h"

#include <lambda_p_script/bool_c/node.h>

void lambda_p_script::if_c::operation::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::bool_c::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::fixed> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (one->value)
			{
				(*two) (errors_a, parameters, results);
			}
			else
			{
				results.insert (results.end (), parameters.begin (), parameters.end ());
			}
		}
		else
		{
			invalid_type (errors_a, 1);
		}
	}
	else
	{
		invalid_type (errors_a, 0);
	}
}

size_t lambda_p_script::if_c::operation::count ()
{
	return 2;
}

std::wstring lambda_p_script::if_c::operation::name ()
{
	return std::wstring (L"lambda_p_script::if_c::operation");
}