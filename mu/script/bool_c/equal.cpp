#include <mu/script/bool_c/equal.h>

#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

bool mu::script::bool_c::equal::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::bool_c::node, mu::script::bool_c::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::script::bool_c::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::script::bool_c::node> (context_a.parameters (1)));
		context_a.push (boost::shared_ptr <mu::script::bool_c::node> (new mu::script::bool_c::node (one->value == two->value)));
	}
	return result;
}

std::wstring mu::script::bool_c::equal::name ()
{
	return std::wstring (L"mu::script::bool_c::equal");
}