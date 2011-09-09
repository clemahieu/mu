#include <lambda_p/parser/routine_parameter.h>

lambda_p::parser::routine_parameter::routine_parameter(::boost::shared_ptr < ::lambda_p::parser::routine> routine_a, ::std::wstring routine_name_a)
	: routine_name (routine_name_a),
	routine (routine_a)
{
}

lambda_p::parser::routine_parameter::~routine_parameter(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::routine_parameter::state_type ()
{
	return ::lambda_p::parser::state_routine_parameter;
}