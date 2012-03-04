#include <mu/script/package.remove.h>

#include <mu/script/package.node.h>
#include <mu/script/string.node.h>
#include <mu/core/errors.error_target.h>

#include <sstream>

void mu::script::package::remove::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::package::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
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
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

std::wstring mu::script::package::remove::name ()
{
	return std::wstring (L"mu::script::package::remove");
}

size_t mu::script::package::remove::count ()
{
	return 2;
}
