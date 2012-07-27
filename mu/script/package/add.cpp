#include <mu/script/package/add.h>

#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/script/context.h>
#include <mu/script/check.h>
#include <mu/core/errors/error_target.h>

#include <sstream>

bool mu::script::package::add::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::package::node, mu::script::string::node, mu::core::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::package::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		auto existing (one->items.find (two->string));
		if (existing != one->items.end ())
		{
			one->items [two->string] = context_a.parameters (2);
		}
		else
		{
			mu::stringstream message;
			message << L"Package already has an item named: ";
			message << two->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}

mu::string mu::script::package::add::name ()
{
	return mu::string (U"mu::script::package::add");
}