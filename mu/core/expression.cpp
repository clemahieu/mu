#include <mu/core/expression.h>

#include <mu/core/visitor.h>

void mu::core::expression::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}