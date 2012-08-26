#include <mu/script/integer_subtract.h>

#include <mu/script/integer_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::integer::subtract::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::integer::node, mu::script::integer::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::integer::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::integer::node *> (context_a.parameters (1)));
		context_a.push (new (GC) mu::script::integer::node (one->value - two->value));
	}
	return result;
}

mu::string mu::script::integer::subtract::name ()
{
	return mu::string (U"mu::script::integer::subtract");
}