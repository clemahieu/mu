#include "reference.h"

#include <lambda_p/visitor.h>

lambda_p::reference::reference (boost::shared_ptr <lambda_p::expression> expression_a, size_t index_a)
	: expression (expression_a),
	index (index_a)
{
}

void lambda_p::reference::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}