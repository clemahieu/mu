#include "remove.h"

#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/error_target.h>

#include <sstream>

void mu::script::package::remove::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::package::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
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
				(*context_a.errors) (message.str ());
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
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