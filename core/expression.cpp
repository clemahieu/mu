#include "expression.h"

#include <core/visitor.h>

mu::core::expression::expression (mu::core::context context_a)
	: context (context_a)
{
}

void mu::core::expression::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}