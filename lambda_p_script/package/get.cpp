#include "get.h"

#include <lambda_p_script/data/node.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

void lambda_p_script::package::get::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto node (boost::dynamic_pointer_cast <lambda_p_script::package::node> (parameters [0]));
	auto name (boost::dynamic_pointer_cast <lambda_p_script::data::node> (parameters [1]));
	if (node.get () != nullptr)
	{
		if (name.get () != nullptr)
		{
			auto existing (node->items.find (name->string));
			if (existing != node->items.end ())
			{
				results.push_back (existing->second);
			}
			else
			{
				std::wstringstream message;
				message << L"Package does not contain item named: ";
				message << name->string;
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

std::wstring lambda_p_script::package::get::name ()
{
	return std::wstring (L"lambda_p_script::package::get");
}

size_t lambda_p_script::package::get::count ()
{
	return 2;
}