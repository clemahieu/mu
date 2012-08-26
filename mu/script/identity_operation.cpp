#include <mu/script/identity_operation.h>

#include <mu/script/context.h>

bool mu::script::identity::operation::operator () (mu::script::context & context_a)
{
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
	{
		context_a.push (*i);
	}
	return true;
}

mu::string mu::script::identity::operation::name ()
{
	return mu::string (U"mu::script::identity::operation");
}