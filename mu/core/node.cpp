#include <mu/core/node.h>

mu::core::node::~node ()
{
}

mu::string mu::core::node::name ()
{
	return mu::string (U"mu::core::node");
}

mu::string mu::core::node::debug ()
{
	return name ();
}