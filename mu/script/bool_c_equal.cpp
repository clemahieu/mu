#include <mu/script/bool_c_equal.h>

#include <mu/script/bool_c_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::bool_c::equal::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::bool_c::node, mu::script::bool_c::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::bool_c::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::bool_c::node *> (context_a.parameters (1)));
		context_a.push (new (GC) mu::script::bool_c::node (one->value == two->value));
	}
	return result;
}

mu::string mu::script::bool_c::equal::name ()
{
	return mu::string (U"mu::script::bool_c::equal");
}