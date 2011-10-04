#include "data.h"

lambda_p::parser::data::data (::boost::shared_ptr < ::lambda_p::parser::statement> statement_a)
	: statement (statement_a)
{
}

lambda_p::parser::data::~data (void)
{
}

::lambda_p::parser::state_id lambda_p::parser::data::state_type ()
{
	return lambda_p::parser::state_data;
}