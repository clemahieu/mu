#include <mu/script/package_remove.h>

#include <mu/script/package_node.h>
#include <mu/script/string_node.h>
#include <mu/core/errors/error_target.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <sstream>

bool mu::script::package::remove::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::package::node, mu::script::string::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::package::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		auto count (one->items.erase (two->string));
		if (count == 0)
		{
			mu::stringstream message;
			message << U"Package already has no item named: ";
			message << two->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}