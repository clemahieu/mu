#include "set.h"

#include <lambda_p/visitor.h>

lambda_p::set::set ()
	: count (~0)
{
}

void lambda_p::set::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}