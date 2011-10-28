#include <lambda_p/parser/association.h>

#include <lambda_p/parser/association_target.h>
#include <lambda_p/binder/data.h>

lambda_p::parser::association::association (boost::shared_ptr < lambda_p::parser::routine> routine_a, boost::shared_ptr < lambda_p::parser::association_target> target_a)
	: on_results (false),
	target (target_a),
	routine (routine_a)
{
}

lambda_p::parser::state_id lambda_p::parser::association::state_type ()
{
	return lambda_p::parser::state_association;
}

boost::function <void (size_t)> lambda_p::parser::association::sink_data ()
{
	boost::function <void (size_t)> result (target->sink_argument ());
	return result;
}