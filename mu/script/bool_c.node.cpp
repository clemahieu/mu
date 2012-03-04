#include <mu/script/bool_c.node.h>

mu::script::bool_c::node::node ()
{
}

mu::script::bool_c::node::node (bool value_a)
	: value (value_a)
{
}

std::wstring mu::script::bool_c::node::debug ()
{
	std::wstring result (value ? std::wstring (L"true") : std::wstring (L"false"));
	return result;
}
