#include <lambda_p/parser/association.h>

#include <lambda_p/parser/association_target.h>
#include <lambda_p/binder/data.h>

lambda_p::parser::association::association (boost::shared_ptr < lambda_p::parser::routine> routine_a, boost::shared_ptr < lambda_p::parser::association_target> target_a)
	: on_results (true),
	target (target_a),
	routine (routine_a)
{
}

lambda_p::parser::state_id lambda_p::parser::association::state_type ()
{
	return lambda_p::parser::state_association;
}

void lambda_p::parser::association::sink_data (size_t * & data)
{
	target->sink_argument (data);
}