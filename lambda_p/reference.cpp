#include "reference.h"

#include <lambda_p/visitor.h>

lambda_p::reference::reference (boost::shared_ptr <lambda_p::set> set_a, size_t index_a)
	: set (set_a),
	index (index_a)
{
}

void lambda_p::reference::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}