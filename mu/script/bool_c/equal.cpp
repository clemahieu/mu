#include "equal.h"

#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

void mu::script::bool_c::equal::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::bool_c::node, mu::script::bool_c::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::bool_c::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::bool_c::node> (context_a.parameters [1]));
		context_a.results.push_back (boost::shared_ptr <mu::script::bool_c::node> (new mu::script::bool_c::node (one->value == two->value)));
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