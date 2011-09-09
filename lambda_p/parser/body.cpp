#include <lambda_p/parser/body.h>

#include <lambda_p/parser/routine.h>

lambda_p::parser::body::body(::boost::shared_ptr < ::lambda_p::parser::routine> routine_a, ::std::wstring routine_name_a, ::std::map < ::std::wstring, size_t> parameter_positions_a)
	: parameter_positions (parameter_positions_a),
	routine_name (routine_name_a),
	routine_m (routine_a)
{
}

lambda_p::parser::body::~body(void)
{
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::parser::body::routine ()
{
	return routine_m->routine_m;
}

::lambda_p::parser::state_id lambda_p::parser::body::state_type ()
{
	return lambda_p::parser::state_body;
}
