#include "operation.h"

#include <mu/script/closure/hole.h>

mu::script::closure::operation::operation (size_t count_a, boost::shared_ptr <mu::script::operation> operation_a)
	: closed (count_a),
	open (count_a),
	operation_m (operation_a)
{
	for (size_t i (0); i != count_a; ++i)
	{
		open [i] = i;
	}
}

mu::script::closure::operation::operation (boost::shared_ptr <mu::script::operation> operation_a, std::vector <size_t> & open_a, std::vector <boost::shared_ptr <mu::core::node>> & closed_a)
	: open (open_a),
	closed (closed_a),
	operation_m (operation_a)
{
}

void mu::script::closure::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	std::vector <size_t> open_l;
	for (size_t position (0), end (parameters.size ()); position != end; ++position)
	{
		auto val (parameters [position]);
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
		results.push_back (boost::shared_ptr <mu::script::closure::operation> (new mu::script::closure::operation (operation_m, open_l, closed)));
	}
	else
	{
		operation_m->perform (errors_a, closed, results);
	}
}

size_t mu::script::closure::operation::count ()
{
	return open.size ();
}

std::wstring mu::script::closure::operation::name ()
{
	return std::wstring (L"mu::script::closure::operation");
}