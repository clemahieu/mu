#include "equal.h"

#include <mu/script/bool_c/node.h>

void mu::script::bool_c::equal::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::bool_c::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::bool_c::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			context_a.results.push_back (boost::shared_ptr <mu::script::bool_c::node> (new mu::script::bool_c::node (one->value == two->value)));
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::script::bool_c::equal::count ()
{
	return 2;
}

std::wstring mu::script::bool_c::equal::name ()
{
	return std::wstring (L"mu::script::bool_c::equal");
}