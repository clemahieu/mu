#include <mu/script/values/create.h>

#include <mu/script/values/operation.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::values::create::operator () (mu::script::context & context_a)
{
	bool result (true);
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> values;
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
	{
		values.push_back (*i);
	}
	context_a.push (new (GC) mu::script::values::operation (values));
	return result;
}