#include <mu/script/closure_single.h>

#include <mu/script/context.h>

mu::script::closure::single::single (mu::core::node * operation_a)
	: operation_m (operation_a)
{
}

mu::script::closure::single::single (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & closed_a, mu::core::node * operation_a)
	: operation_m (operation_a),
	closed (closed_a)
{
}

bool mu::script::closure::single::operator () (mu::script::context & context_a)
{
	bool result (true);
	context_a.push (operation_m);
	for (auto i (closed.begin ()), j (closed.end ()); i != j; ++i)
	{
		context_a.push (*i);
	}
	context_a.push (context_a.parameters_begin (), context_a.parameters_end ());
	result = context_a ();
	return result;
}