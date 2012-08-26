#include <mu/script/integer_node.h>

#include <sstream>

mu::script::integer::node::node ()
{
}

mu::script::integer::node::node (unsigned long long value_a)
	: value (value_a)
{
}

mu::string mu::script::integer::node::name ()
{
	return mu::string (U"mu::script::integer::node");
}

mu::string mu::script::integer::node::debug ()
{
	mu::stringstream result;
	result << value;
	return result.str ();
}