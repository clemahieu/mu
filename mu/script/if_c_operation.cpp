#include <mu/script/if_c_operation.h>

#include <mu/script/bool_c_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

bool mu::script::if_c::operation::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::bool_c::node, mu::script::operation, mu::script::operation> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::bool_c::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::operation *> (context_a.parameters (1)));
		auto three (static_cast <mu::script::operation *> (context_a.parameters (2)));
		mu::vector <mu::core::node *> arguments;
		if (one->value)
		{
			context_a.push (two);
		}
		else
		{
			context_a.push (three);
		}
		for (auto i (context_a.parameters_begin () + 3), j (context_a.parameters_end ()); i != j; ++i)
		{
			context_a.push (*i);
		}
		result = context_a ();
	}
	return result;
}