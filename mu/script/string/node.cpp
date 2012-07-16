#include <mu/script/string/node.h>

#include <sstream>

mu::script::string::node::node (mu::string string_a)
	: string (string_a)
{
}

mu::string mu::script::string::node::debug ()
{
	mu::stringstream result;
	result << L"\"";
	result << string;
	result << L"\"";
	return result.str ();
}

mu::string mu::script::string::node::name ()
{
	return mu::string (U"mu::script::string::node");
}