#include <mu/script/string_node.h>

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