#include <mu/script/closure_create.h>

#include <mu/script/closure_operation.h>
#include <mu/script/integer_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::closure::create::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::operation, mu::script::integer::node> (context_a));
	if (result)
	{
		auto operation (static_cast <mu::script::operation *> (context_a.parameters (0)));
		auto count (static_cast <mu::script::integer::node *> (context_a.parameters (1)));
		context_a.push (new (GC) mu::script::closure::operation (count->value, operation));
	}
	return result;
}

mu::string mu::script::closure::create::name ()
{
	return mu::string (U"mu::script::closure::create");
}