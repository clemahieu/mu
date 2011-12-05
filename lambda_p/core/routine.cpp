#include <lambda_p/core/routine.h>

#include <lambda_p/errors/orphan_node.h>
#include <lambda_p/errors/orphan_reference.h>
#include <lambda_p/errors/undefined_reference.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p/errors/node_out_of_order.h>

#include <algorithm>

lambda_p::core::routine::routine (std::vector <lambda_p::core::expression *> & surface_a, lambda_p::core::expression * routine_expression_a)
	: surface (surface_a),
	routine_expression (routine_expression_a)
{
}