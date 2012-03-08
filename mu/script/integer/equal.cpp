#include "equal.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/integer/node.h>
#include <mu/script/bool_c/node.h>

void mu::script::integer::equal::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
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

std::wstring mu::script::integer::equal::name ()
{
	return std::wstring (L"mu::script::integer::equal");
}

size_t mu::script::integer::equal::count ()
{
	return 2;
}