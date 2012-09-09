#include <mu/script/identity.h>

#include <mu/script/context.h>

bool mu::script::identity::operator () (mu::script::context & context_a)
{
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
	{
		context_a.push (*i);
	}
	return true;
}