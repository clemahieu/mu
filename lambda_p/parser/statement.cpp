#include "statement.h"

#include <lambda_p/parser/body.h>

lambda_p::parser::statement::statement(::boost::shared_ptr < ::lambda_p::parser::body> body_a, ::std::wstring statement_name_a)
	: statement_name (statement_name_a),
	body (body_a),
	have_target (false),
	have_argument (false),
	statement_m (body_a->routine ()->add_statement ())
{
}

lambda_p::parser::statement::~statement(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::statement::state_type ()
{
	return lambda_p::parser::state_statement;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::parser::statement::routine ()
{
	return body->routine ();
}