#include <mu/script/runtime/expression.h>

#include <mu/script/context.h>
#include <mu/script/check.h>
#include <mu/script/runtime/locals.h>
#include <mu/script/runtime/reference.h>

bool mu::script::runtime::expression::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::script::runtime::locals> (context_a));
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