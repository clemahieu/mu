#include <mu/script/integer/subtract.h>

#include <mu/script/integer/node.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::script::integer::subtract::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::integer::node, mu::script::integer::node> (context_a));
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