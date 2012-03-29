#include <mu/core/parameters.h>

#include <mu/core/visitor.h>

void mu::core::parameters::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}