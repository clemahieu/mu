#include "individual.h"

#include <lambda_p/core/scatter.h>

lambda_p_io::analyzer::individual::individual (boost::shared_ptr <lambda_p::core::scatter> scatter_a, size_t index_a)
	: scatter (scatter_a),
	index (index_a)
{
}

void lambda_p_io::analyzer::individual::operator () (boost::shared_ptr <lambda_p::core::target> target_a)
{
	(*scatter) [index].push_back (target_a);
}