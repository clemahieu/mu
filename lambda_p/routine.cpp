#include "routine.h"

#include <lambda_p/expression.h>

#include <lambda_p/visitor.h>

lambda_p::routine::routine (lambda_p::context context_a)
	: parameters (new lambda_p::expression (context_a))
{
}

void lambda_p::routine::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}