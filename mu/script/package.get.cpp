#include <mu/script/package.get.h>

#include <mu/script/string.node.h>
#include <mu/script/package.node.h>
#include <mu/core/errors.error_target.h>

#include <sstream>

void mu::script::package::get::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto node (boost::dynamic_pointer_cast <mu::script::package::node> (parameters [0]));
	auto name (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
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
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

std::wstring mu::script::package::get::name ()
{
	return std::wstring (L"mu::script::package::get");
}

size_t mu::script::package::get::count ()
{
	return 2;
}
