#include "single.h"

mu::script::closure::single::single (boost::shared_ptr <mu::script::operation> operation_a)
	: operation_m (operation_a)
{
}

mu::script::closure::single::single (std::vector <boost::shared_ptr <mu::core::node>> & closed_a, boost::shared_ptr <mu::script::operation> operation_a)
	: closed (closed_a),
	operation_m (operation_a)
{
}

void mu::script::closure::single::perform (mu::script::context & context_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> closed_l (closed.begin (), closed.end ());
	closed_l.insert (closed_l.end (), context_a.parameters.begin (), context_a.parameters.end ());
	operation_m->perform (mu::script::context (context_a.errors, closed_l, context_a.results));
}

std::wstring mu::script::closure::single::name ()
{
	return std::wstring (L"mu::script::closure::single");
}