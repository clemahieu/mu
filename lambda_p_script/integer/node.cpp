#include "node.h"

#include <sstream>

lambda_p_script::integer::node::node ()
{
}

lambda_p_script::integer::node::node (unsigned long long value_a)
	: value (value_a)
{
}

std::wstring lambda_p_script::integer::node::name ()
{
	return std::wstring (L"lambda_p_script::integer::node");
}

std::wstring lambda_p_script::integer::node::debug ()
{
	std::wstringstream result;
	result << value;
	return result.str ();
}