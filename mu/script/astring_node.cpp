#include <mu/script/astring_node.h>

#include <sstream>

mu::script::astring::node::node ()
{
}

mu::script::astring::node::node (std::string string_a)
	: string (string_a)
{
}

mu::string mu::script::astring::node::name ()
{
	return mu::string (U"mu::script::astring::node");
}

mu::string mu::script::astring::node::debug ()
{
	mu::stringstream message;
	message << U"\"";
	mu::string string_l (string.begin (), string.end ());
	message << string_l;
	message << U"\"";
	return message.str ();
}