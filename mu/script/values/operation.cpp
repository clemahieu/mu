#include <mu/script/values/operation.h>

#include <mu/core/check.h>
#include <mu/script/context.h>

mu::script::values::operation::operation ()
{
}

mu::script::values::operation::operation (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> values_a)
	: values (values_a)
{
}

bool mu::script::values::operation::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <> (context_a));
	if (result)
	{
		for (auto i (values.begin ()), j (values.end ()); i != j; ++i)
		{
			context_a.push (*i);
		}
	}
	return result;
}