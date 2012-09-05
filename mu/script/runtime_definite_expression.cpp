#include <mu/script/runtime_definite_expression.h>

#include <mu/script/context.h>
#include <mu/core/check.h>
#include <mu/script/runtime_locals.h>
#include <mu/script/runtime_reference.h>

bool mu::script::runtime::definite_expression::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::script::runtime::locals> (context_a));
	if (valid)
	{
		for (auto i (dependencies.begin ()), j (dependencies.end ()); i != j; ++i)
		{
			context_a.push (*i);
			context_a.push (context_a.parameters (0));
			valid = valid && context_a ();
			context_a.slide ();
		}
		if (valid)
		{
			context_a.push (context_a.locals_begin (), context_a.locals_end ());
			valid = context_a ();
		}
	}
	return valid;
}