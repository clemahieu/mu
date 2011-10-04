#include "data.h"

lambda_p::parser::data::data (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::boost::shared_ptr < ::lambda_p::parser::data_target> target_a)
	: target (target_a),
	routine (routine_a)
{
}

lambda_p::parser::data::~data (void)
{
}

::lambda_p::parser::state_id lambda_p::parser::data::state_type ()
{
	return lambda_p::parser::state_data;
}