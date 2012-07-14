#include <mu/script/integer/equal.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/integer/node.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::script::integer::equal::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::integer::node, mu::script::integer::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::integer::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::integer::node *> (context_a.parameters (1)));
		context_a.push (new (GC) mu::script::bool_c::node (one->value == two->value));
	}
	return result;
}

std::wstring mu::script::integer::equal::name ()
{
	return std::wstring (L"mu::script::integer::equal");
}