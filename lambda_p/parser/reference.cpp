#include "reference.h"

lambda_p::parser::reference::reference(::std::wstring target_statement_a, ::boost::shared_ptr < ::lambda_p::parser::statement> statement_a)
	: statement (statement_a),
	target_statement (target_statement_a)
{
}

lambda_p::parser::reference::~reference(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::reference::state_type ()
{
	return lambda_p::parser::state_result_ref;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::parser::reference::routine ()
{
	return statement->routine ();
}
