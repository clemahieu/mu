#include "apply.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/closure/operation.h>
#include <lambda_p_script/closure/hole.h>

#include <sstream>

void lambda_p_script::closure::apply::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto operation (boost::dynamic_pointer_cast <lambda_p_script::closure::operation> (parameters [0]));
		if (operation.get () != nullptr)
		{			
			std::vector <size_t> open_l;
			for (size_t position (1), end (parameters.size ()); position != end; ++position)
			{
				auto val (parameters [position]);
				auto hole (boost::dynamic_pointer_cast <lambda_p_script::closure::hole> (val));
				if (hole.get () == nullptr)
				{
					operation->closed [operation->open [position - 1]] = val;
				}
				else
				{
					open_l.push_back (operation->open [position - 1]);
				}
				results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::operation (operation->operation_m, open_l, operation->closed)));
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
		message << L" must have at least one argument";
		(*errors_a) (message.str ());
	}
}

std::wstring lambda_p_script::closure::apply::name ()
{
	return std::wstring (L"lambda_p_script::closure::apply");
}