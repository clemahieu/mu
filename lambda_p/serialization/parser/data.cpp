#include "data.h"

lambda_p::serialization::parser::data::data (::lambda_p::serialization::parser::statement * statement_a)
	: statement (statement_a)
{
}

lambda_p::serialization::parser::data::~data (void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::data::state_type ()
{
	return lambda_p::serialization::parser::state_data;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::serialization::parser::data::routine ()
{
	return statement->routine ();
}
