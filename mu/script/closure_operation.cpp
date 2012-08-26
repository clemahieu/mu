#include <mu/script/closure_operation.h>

#include <mu/script/closure_hole.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

mu::script::closure::operation::operation (size_t count_a, mu::script::operation * operation_a)
	: operation_m (operation_a),
    open (count_a),
	closed (count_a)
{
	for (size_t i (0); i != count_a; ++i)
	{
		open [i] = i;
	}
}

mu::script::closure::operation::operation (mu::script::operation * operation_a, std::vector <size_t> & open_a, std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & closed_a)
	: operation_m (operation_a),
	open (open_a),
    closed (closed_a)
{
}

bool mu::script::closure::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () == open.size ())
	{
		std::vector <size_t> open_l;
		for (size_t position (0), end (context_a.parameters_size ()); position != end; ++position)
		{
			auto val (context_a.parameters (position));
			auto hole (dynamic_cast <mu::script::closure::hole *> (val));
			if (hole == nullptr)
			{
				closed [open [position]] = val;
			}
			else
			{
				open_l.push_back (open [position]);
			}
		}
		if (open_l.size () != 0)
		{
			context_a.push (new (GC) mu::script::closure::operation (operation_m, open_l, closed));
		}
		else
		{
			context_a.push (operation_m);
			context_a.push (closed.begin (), closed.end ());
			result = context_a ();
		}
	}
	return result;
}

mu::string mu::script::closure::operation::name ()
{
	return mu::string (U"mu::script::closure::operation");
}