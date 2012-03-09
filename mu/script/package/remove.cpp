#include "remove.h"

#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/check.h>

#include <sstream>

void mu::script::package::remove::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::package::node, mu::script::string::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::package::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
		auto count (one->items.erase (two->string));
		if (count == 0)
		{
			std::wstringstream message;
			message << L"Package already has no item named: ";
			message << two->string;
			(*context_a.errors) (message.str ());
		}
	}
}

std::wstring mu::script::package::remove::name ()
{
	return std::wstring (L"mu::script::package::remove");
}