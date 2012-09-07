#include <mu/script/package_get.h>

#include <mu/script/string_node.h>
#include <mu/script/package_node.h>
#include <mu/core/errors/error_target.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <sstream>

bool mu::script::package::get::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::package::node, mu::script::string::node> (context_a));
	if (result)
	{
		auto node (static_cast <mu::script::package::node *> (context_a.parameters (0)));
		auto name (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		auto existing (node->items.find (name->string));
		if (existing != node->items.end ())
		{
			context_a.push (existing->second);
		}
		else
		{
			mu::stringstream message;
			message << U"Package does not contain item named: ";
			message << name->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}