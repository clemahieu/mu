#include "operation.h"

#include <mu/script/closure/hole.h>
#include <mu/script/check.h>

mu::script::closure::operation::operation (size_t count_a, boost::shared_ptr <mu::script::operation> operation_a)
	: operation_m (operation_a),
    open (count_a),
	closed (count_a)
{
	for (size_t i (0); i != count_a; ++i)
	{
		open [i] = i;
	}
}

mu::script::closure::operation::operation (boost::shared_ptr <mu::script::operation> operation_a, std::vector <size_t> & open_a, std::vector <boost::shared_ptr <mu::core::node>> & closed_a)
	: operation_m (operation_a),
	open (open_a),
    closed (closed_a)
{
}

void mu::script::closure::operation::operator () (mu::script::context & context_a)
{
	if (mu::script::check_count (context_a.errors, context_a.parameters, open.size ()))
	{
		std::vector <size_t> open_l;
		for (size_t position (0), end (context_a.parameters.size ()); position != end; ++position)
		{
			auto val (context_a.parameters [position]);
			auto hole (boost::dynamic_pointer_cast <mu::script::closure::hole> (val));
			if (hole.get () == nullptr)
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
			context_a.results.push_back (boost::shared_ptr <mu::script::closure::operation> (new mu::script::closure::operation (operation_m, open_l, closed)));
		}
		else
		{
			auto ctx (mu::script::context (context_a.errors, closed, context_a.results));
			(*operation_m) (ctx);
		}
	}
}

std::wstring mu::script::closure::operation::name ()
{
	return std::wstring (L"mu::script::closure::operation");
}