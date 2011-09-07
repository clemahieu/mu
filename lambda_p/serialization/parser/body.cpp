#include <lambda_p/serialization/parser/body.h>

lambda_p::serialization::parser::body::body(::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::std::wstring routine_name_a, ::std::map < ::std::wstring, size_t> parameter_positions_a)
	: parameter_positions (parameter_positions_a),
	routine_name (routine_name_a),
	statement_count (0),
	routine (routine_a)
{
}

lambda_p::serialization::parser::body::~body(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::body::state_type ()
{
	return lambda_p::serialization::parser::state_body;
}
