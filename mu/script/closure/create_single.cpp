#include <mu/script/closure/create_single.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/single.h>
#include <mu/script/check.h>

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
		message << L"Operation: ";
		message << name ();
		message << L" must have at least one argument";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

mu::string mu::script::closure::create_single::name ()
{
	return mu::string (U"mu::script::closure::create_single");
}