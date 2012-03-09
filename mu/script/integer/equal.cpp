#include "equal.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/integer/node.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

void mu::script::integer::equal::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::integer::node, mu::script::integer::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
		context_a.results.push_back (boost::shared_ptr <mu::script::bool_c::node> (new mu::script::bool_c::node (one->value == two->value)));
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