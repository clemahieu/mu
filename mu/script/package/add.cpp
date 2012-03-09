#include "add.h"

#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/check.h>

#include <sstream>

void mu::script::package::add::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::package::node, mu::script::string::node, mu::core::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::package::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
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
}

std::wstring mu::script::package::add::name ()
{
	return std::wstring (L"mu::script::package::add");
}