#include "hex_data.h"

lambda_p::parser::hex_data::hex_data (::boost::shared_ptr < ::lambda_p::parser::statement> statement_a)
	: statement (statement_a)
{
}

lambda_p::parser::hex_data::~hex_data (void)
{
}

::lambda_p::parser::state_id lambda_p::parser::hex_data::state_type ()
{
	return lambda_p::parser::state_hex_data;
}
