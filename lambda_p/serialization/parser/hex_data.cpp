#include "hex_data.h"

lambda_p::serialization::parser::hex_data::hex_data (::lambda_p::serialization::parser::statement * statement_a)
	: statement (statement_a)
{
}

lambda_p::serialization::parser::hex_data::~hex_data (void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::hex_data::state_type ()
{
	return lambda_p::serialization::parser::state_hex_data;
}
