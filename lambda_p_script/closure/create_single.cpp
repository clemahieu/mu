#include "create_single.h"

#include <mu/core/errors/error_target.h>
#include <lambda_p_script/closure/operation.h>
#include <lambda_p_script/closure/single.h>

#include <sstream>

void lambda_p_script::closure::create_single::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_script::operation> (parameters [0]));
		if (one.get () != nullptr)
		{
			std::vector <boost::shared_ptr <mu::core::node>> closed_l (parameters.begin () + 1, parameters.end ());
			results.push_back (boost::shared_ptr <mu::core::node> (new lambda_p_script::closure::single (closed_l, one)));
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" must have at least one argument";
		(*errors_a) (message.str ());
	}
}

std::wstring lambda_p_script::closure::create_single::name ()
{
	return std::wstring (L"lambda_p_script::closure::create_single");
}