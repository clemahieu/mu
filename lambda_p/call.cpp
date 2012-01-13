#include "call.h"

#include <lambda_p/visitor.h>

void lambda_p::call::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}