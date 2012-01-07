#include "parameters.h"

#include <lambda_p/visitor.h>

lambda_p::parameters::parameters ()
	: count (~0)
{
}

void lambda_p::parameters::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}