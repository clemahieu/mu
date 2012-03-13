#include <mu/core/expression.h>

#include <mu/core/visitor.h>

mu::core::expression::expression (mu::core::context context_a)
	: context (context_a)
{
}

void mu::core::expression::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}