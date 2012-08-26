#include <mu/script/bool_c_node.h>

mu::script::bool_c::node::node ()
{
}

mu::script::bool_c::node::node (bool value_a)
	: value (value_a)
{
}

mu::string mu::script::bool_c::node::debug ()
{
	mu::string result (value ? mu::string (U"true") : mu::string (U"false"));
	return result;
}