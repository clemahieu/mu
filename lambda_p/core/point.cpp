#include "point.h"

#include <lambda_p/core/gather.h>

lambda_p::core::point::point (boost::shared_ptr <lambda_p::core::gather> target_a, size_t index_a)
	: target (target_a),
	index (index_a)
{
}

void lambda_p::core::point::operator () (boost::shared_ptr <lambda_p::core::expression> expression_a)
{
	(*target) (expression_a, index);
}