#include "get.h"

#include <mu/script/string/node.h>
#include <mu/script/package/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/check.h>

#include <sstream>

void mu::script::package::get::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::package::node, mu::script::string::node> () (context_a))
	{
		auto node (boost::static_pointer_cast <mu::script::package::node> (context_a.parameters [0]));
		auto name (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
		auto existing (node->items.find (name->string));
		if (existing != node->items.end ())
		{
			context_a.results.push_back (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Package does not contain item named: ";
			message << name->string;
			(*context_a.errors) (message.str ());
		}
	}
}

std::wstring mu::script::package::get::name ()
{
	return std::wstring (L"mu::script::package::get");
}