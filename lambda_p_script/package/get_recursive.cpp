#include "get_recursive.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_script/package/get.h>

#include <sstream>

void lambda_p_script::package::get_recursive::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto node (parameters [0]);
		bool good (true);
		auto i (parameters.begin () + 1);
		auto j (parameters.end ());
		for (; i != j && good; ++i)
		{
			lambda_p_script::package::get get;
			std::vector <boost::shared_ptr <lambda_p::node>> arguments;
			std::vector <boost::shared_ptr <lambda_p::node>> results_l;
			arguments.push_back (node);
			arguments.push_back (*i);
			get (errors_a, arguments, results_l);
			if (results_l.size () == 1)
			{
				node = results_l [0];
			}
			else
			{
				good = false;
				(*errors_a) (L"Get operation did not return result");
			}
		}
		results.push_back (node);
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" requires at least one argument";
		(*errors_a) (message.str ());
	}
}

std::wstring lambda_p_script::package::get_recursive::name ()
{
	return std::wstring (L"lambda_p_script::package::get_recursive");
}