#include "node.h"

#include <core/visitor.h>

mu::core::node::~node ()
{
}

void mu::core::node::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring mu::core::node::name ()
{
	return std::wstring (L"mu::core::node");
}

std::wstring mu::core::node::debug ()
{
	return name ();
}