#include <lambda_p/core/routine.h>

lambda_p::core::routine::routine (std::vector <lambda_p::core::expression_leaf *> & surface_a, lambda_p::core::expression * routine_expression_a)
	: surface (surface_a),
	routine_expression (routine_expression_a)
{
}