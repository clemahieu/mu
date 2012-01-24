#include "expression.h"

#include <lambda_p/visitor.h>

lambda_p::expression::expression (lambda_p::context context_a)
	: context (context_a)
{
}

void lambda_p::expression::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}