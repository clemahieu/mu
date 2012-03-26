#include <mu/script/astring/node.h>

#include <sstream>

mu::script::astring::node::node ()
{
}

mu::script::astring::node::node (std::string string_a)
	: string (string_a)
{
}

std::wstring mu::script::astring::node::name ()
{
	return std::wstring (L"mu::script::astring::node");
}

std::wstring mu::script::astring::node::debug ()
{
	std::wstringstream message;
	message << L"\"";
	std::wstring string_l (string.begin (), string.end ());
	message << string_l;
	message << L"\"";
	return message.str ();
}