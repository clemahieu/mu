#include "reference_scatter.h"

#include <lambda_p/core/scatter.h>

lambda_p_serialization::parser::reference_scatter::reference_scatter (boost::shared_ptr <lambda_p::core::scatter> scatter_a, size_t position_a)
	: scatter (scatter_a),
	position (position_a)
{
}

void lambda_p_serialization::parser::reference_scatter::operator () (boost::shared_ptr <lambda_p::core::target> target_a)
{
	(*scatter) [position].push_back (target_a);
}