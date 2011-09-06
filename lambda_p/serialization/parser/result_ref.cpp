#include "result_ref.h"

lambda_p::serialization::parser::result_ref::result_ref(::std::wstring target_statement_a, ::lambda_p::serialization::parser::statement * statement_a)
	: statement (statement_a),
	target_statement (target_statement_a)
{
}

lambda_p::serialization::parser::result_ref::~result_ref(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::statement::state_type ()
{
	return lambda_p::serialization::parser::state_statement;
}
