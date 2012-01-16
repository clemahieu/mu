#include "node.h"

lambda_p_script::bool_c::node::node ()
{
}

lambda_p_script::bool_c::node::node (bool value_a)
	: value (value_a)
{
}

std::wstring lambda_p_script::bool_c::node::debug ()
{
	std::wstring result (value ? std::wstring (L"true") : std::wstring (L"false"));
	return result;
}