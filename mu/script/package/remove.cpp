#include <mu/script/package/remove.h>

#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/check.h>

#include <sstream>

bool mu::script::package::remove::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::package::node, mu::script::string::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::package::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		auto count (one->items.erase (two->string));
		if (count == 0)
		{
			std::wstringstream message;
			message << L"Package already has no item named: ";
			message << two->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}

std::wstring mu::script::package::remove::name ()
{
	return std::wstring (L"mu::script::package::remove");
}