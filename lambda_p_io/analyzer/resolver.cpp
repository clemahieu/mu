#include "resolver.h"

lambda_p_io::analyzer::resolver::resolver (boost::shared_ptr <lambda_p_io::analyzer::unresolved> unresolved_a, boost::shared_ptr <lambda_p::expression> expression_a, size_t index_a)
	: unresolved (unresolved),
	expression (expression_a),
	index (index_a)
{
}