#include <lambda_p/serialization/parser/routine_parameter.h>

lambda_p::serialization::parser::routine_parameter::routine_parameter(::boost::shared_ptr < ::lambda_p::serialization::parser::routine> routine_a, ::std::wstring routine_name_a)
	: routine_name (routine_name_a),
	routine (routine_a)
{
}

lambda_p::serialization::parser::routine_parameter::~routine_parameter(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::routine_parameter::state_type ()
{
	return ::lambda_p::serialization::parser::state_routine_parameter;
}