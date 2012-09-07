#include <mu/script/closure_create_single.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/closure_operation.h>
#include <mu/script/closure_single.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::script::closure::create_single::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		std::vector <mu::core::node *, gc_allocator <mu::core::node *>> closed_l;
		for (auto i (context_a.parameters_begin () + 1), j (context_a.parameters_end ()); i != j; ++i)
		{
			closed_l.push_back (*i);
		}
		context_a.push (new (GC) mu::script::closure::single (closed_l, context_a.parameters (0)));
	}
	else
	{
		mu::stringstream message;
		message << U"Operation: ";
		message << name ();
		message << U" must have at least one argument";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}