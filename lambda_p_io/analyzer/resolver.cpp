#include "resolver.h"

#include <lambda_p/expression.h>

lambda_p_io::analyzer::resolver::resolver (boost::shared_ptr <lambda_p_io::analyzer::unresolved> unresolved_a, boost::shared_ptr <lambda_p::expression> expression_a)
	: unresolved (unresolved_a),
	expression (expression_a),
	index (expression_a->dependencies.size ())
{
}