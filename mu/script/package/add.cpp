#include "add.h"

#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/error_target.h>

#include <sstream>

void mu::script::package::add::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::package::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto existing (one->items.find (two->string));
			if (existing != one->items.end ())
			{
				one->items.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (two->string, context_a.parameters [2]));
			}
			else
			{
				std::wstringstream message;
				message << L"Package already has an item named: ";
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

std::wstring mu::script::package::add::name ()
{
	return std::wstring (L"mu::script::package::add");
}

size_t mu::script::package::add::count ()
{
	return 3;
}