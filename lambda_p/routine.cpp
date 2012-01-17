#include "routine.h"

#include <lambda_p/expression.h>

#include <lambda_p/visitor.h>

lambda_p::routine::routine ()
	: parameters (new lambda_p::expression)
{
}

void lambda_p::routine::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}