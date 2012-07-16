#include <mu/script/closure/create.h>

#include <mu/script/closure/operation.h>
#include <mu/script/integer/node.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::script::closure::create::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::operation, mu::script::integer::node> () (context_a));
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