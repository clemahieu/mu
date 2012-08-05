#include <mu/script/string/node.h>

#include <sstream>

mu::script::string::node::node (mu::string string_a)
	: string (string_a)
{
}

mu::string mu::script::string::node::debug ()
{
	mu::stringstream result;
	result << U'\"';
	result << string;
	result << U'\"';
    auto val (result.str ());
	return val;
}

mu::string mu::script::string::node::name ()
{
	return mu::string (U"mu::script::string::node");
}