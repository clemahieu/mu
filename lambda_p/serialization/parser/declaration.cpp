#include "declaration.h"

lambda_p::serialization::parser::declaration::declaration (::lambda_p::serialization::parser::statement * statement_a)
	: statement (statement_a)
{
}

lambda_p::serialization::parser::declaration::~declaration (void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::declaration::state_type ()
{
	return lambda_p::serialization::parser::state_declaration;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::serialization::parser::declaration::routine ()
{
	return statement->routine ();
}
