#include <lambda_p/serialization/parser/body.h>

#include <lambda_p/serialization/parser/routine.h>

lambda_p::serialization::parser::body::body(::lambda_p::serialization::parser::routine * routine_a, ::std::wstring routine_name_a, ::std::map < ::std::wstring, size_t> parameter_positions_a)
	: parameter_positions (parameter_positions_a),
	routine_name (routine_name_a),
	routine_m (routine_a)
{
}

lambda_p::serialization::parser::body::~body(void)
{
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::serialization::parser::body::routine ()
{
	return routine_m->routine_m;
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::body::state_type ()
{
	return lambda_p::serialization::parser::state_body;
}
