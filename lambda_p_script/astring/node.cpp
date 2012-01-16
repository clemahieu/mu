#include "node.h"

#include <sstream>

lambda_p_script::astring::node::node (std::string string_a)
	: string (string_a)
{
}

std::wstring lambda_p_script::astring::node::name ()
{
	return std::wstring (L"lambda_p_script::astring::node");
}

std::wstring lambda_p_script::astring::node::debug ()
{
	std::wstringstream message;
	message << L"\"";
	std::wstring string_l (string.begin (), string.end ());
	message << string_l;
	message << L"\"";
	return message.str ();
}