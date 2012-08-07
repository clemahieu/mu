#include <mu/script/bool_c/equal.h>

#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::script::bool_c::equal::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::bool_c::node, mu::script::bool_c::node> (context_a));
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