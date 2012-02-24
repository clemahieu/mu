#include "get_recursive.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/script/package/get.h>

#include <sstream>

void mu::script::package::get_recursive::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto node (parameters [0]);
		bool good (true);
		auto i (parameters.begin () + 1);
		auto j (parameters.end ());
		for (; i != j && good; ++i)
		{
			mu::script::package::get get;
			std::vector <boost::shared_ptr <mu::core::node>> arguments;
			std::vector <boost::shared_ptr <mu::core::node>> results_l;
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

std::wstring mu::script::package::get_recursive::name ()
{
	return std::wstring (L"mu::script::package::get_recursive");
}