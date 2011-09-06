#include <lambda_p/serialization/parser/body.h>

lambda_p::serialization::parser::body::body(::boost::shared_ptr < ::std::map < ::lambda_p::serialization::parser::result_reference, ::lambda_p::serialization::parser::result_position> > positions_a)
	: positions (positions_a),
	statement_count (0)
{
}

lambda_p::serialization::parser::body::~body(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::body::state_type ()
{
	return lambda_p::serialization::parser::state_body;
}
