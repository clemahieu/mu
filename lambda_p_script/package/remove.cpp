#include "remove.h"

#include <lambda_p_script/package/node.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

void lambda_p_script::package::remove::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::package::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto count (one->items.erase (two->string));
			if (count == 0)
			{
				std::wstringstream message;
				message << L"Package already has no item named: ";
				message << two->string;
				(*errors_a) (message.str ());
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

std::wstring lambda_p_script::package::remove::name ()
{
	return std::wstring (L"lambda_p_script::package::remove");
}

size_t lambda_p_script::package::remove::count ()
{
	return 2;
}