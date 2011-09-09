#include "reference.h"

lambda_p::serialization::parser::reference::reference(::std::wstring target_statement_a, ::lambda_p::serialization::parser::statement * statement_a)
	: statement (statement_a),
	target_statement (target_statement_a)
{
}

lambda_p::serialization::parser::reference::~reference(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::reference::state_type ()
{
	return lambda_p::serialization::parser::state_result_ref;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::serialization::parser::reference::routine ()
{
	return statement->routine ();
}
