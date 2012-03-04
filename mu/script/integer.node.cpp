#include "node.h"

#include <sstream>

mu::script::integer::node::node ()
{
}

mu::script::integer::node::node (unsigned long long value_a)
	: value (value_a)
{
}

std::wstring mu::script::integer::node::name ()
{
	return std::wstring (L"mu::script::integer::node");
}

std::wstring mu::script::integer::node::debug ()
{
	std::wstringstream result;
	result << value;
	return result.str ();
}