#include <mu/script/string/node.h>

#include <sstream>

mu::script::string::node::node (std::wstring string_a)
	: string (string_a)
{
}

std::wstring mu::script::string::node::debug ()
{
	std::wstringstream result;
	result << L"\"";
	result << string;
	result << L"\"";
	return result.str ();
}

std::wstring mu::script::string::node::name ()
{
	return std::wstring (L"mu::script::string::node");
}