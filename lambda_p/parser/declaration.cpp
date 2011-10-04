#include "declaration.h"

lambda_p::parser::declaration::declaration (::boost::shared_ptr < ::lambda_p::parser::statement> statement_a)
	: statement (statement_a)
{
}

lambda_p::parser::declaration::~declaration (void)
{
}

::lambda_p::parser::state_id lambda_p::parser::declaration::state_type ()
{
	return lambda_p::parser::state_declaration;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::parser::declaration::routine ()
{
	return statement->routine ();
}
