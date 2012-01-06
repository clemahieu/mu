#include "resolver.h"

#include <lambda_p/call.h>

lambda_p_io::analyzer::resolver::resolver (boost::shared_ptr <lambda_p_io::analyzer::unresolved> unresolved_a, boost::shared_ptr <lambda_p::call> call_a)
	: unresolved (unresolved_a),
	call (call_a),
	index (call_a->dependencies.size ())
{
}