#include <mu/core/cluster.h>

#include <mu/core/visitor.h>

void mu::core::cluster::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring mu::core::cluster::name ()
{
	return std::wstring (L"mu::core::cluster");
}