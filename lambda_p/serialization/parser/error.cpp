#include <lambda_p/serialization/parser/error.h>

lambda_p::serialization::parser::error::error(void)
{
}

lambda_p::serialization::parser::error::~error(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::error::state_type ()
{
	return lambda_p::serialization::parser::state_error;
}
