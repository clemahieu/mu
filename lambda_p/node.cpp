#include "node.h"

#include <lambda_p/visitor.h>

lambda_p::node::~node ()
{
}

void lambda_p::node::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}