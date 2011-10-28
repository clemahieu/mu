#include "position_set.h"

#include <lambda_p/core/association.h>

lambda_p::parser::position_set::position_set (std::vector <size_t> & target_a, size_t position_a)
	: target (target_a),
	position (position_a)
{
}

void lambda_p::parser::position_set::operator() (size_t declaration)
{
	target [position] = declaration;
}
