#include <mu/core/cluster.h>

#include <mu/core/visitor.h>

void mu::core::cluster::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}

mu::string mu::core::cluster::name ()
{
	return mu::string (U"mu::core::cluster");
}