#include "get_recursive.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/script/package/get.h>
#include <mu/script/context.h>

#include <sstream>

void mu::script::package::get_recursive::operator () (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 0)
	{
		auto node (context_a.parameters [0]);
		bool good (true);
		auto i (context_a.parameters.begin () + 1);
		auto j (context_a.parameters.end ());
		for (; i != j && good; ++i)
		{
			mu::script::package::get get;
			std::vector <boost::shared_ptr <mu::core::node>> arguments;
			std::vector <boost::shared_ptr <mu::core::node>> results_l;
			arguments.push_back (node);
			arguments.push_back (*i);
            auto ctx (mu::script::context (context_a.errors, arguments, results_l));
			get (ctx);
			if (results_l.size () == 1)
			{
				node = results_l [0];
			}
			else
			{
				good = false;
				(*context_a.errors) (L"Get operation did not return result");
			}
		}
		context_a.results.push_back (node);
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" requires at least one argument";
		(*context_a.errors) (message.str ());
	}
}

std::wstring mu::script::package::get_recursive::name ()
{
	return std::wstring (L"mu::script::package::get_recursive");
}