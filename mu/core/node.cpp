#include <mu/core/node.h>

#include <mu/core/visitor.h>

mu::core::node::~node ()
{
}

void mu::core::node::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}

mu::string mu::core::node::name ()
{
	return mu::string (U"mu::core::node");
}

mu::string mu::core::node::debug ()
{
	return name ();
}