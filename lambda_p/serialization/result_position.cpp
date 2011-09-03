#include "result_position.h"

lambda_p::serialization::result_position::result_position ()
	: statement (-1),
	argument (-1)
{
}

lambda_p::serialization::result_position::result_position (size_t statement_a, size_t argument_a)
	:statement (statement_a),
	argument (argument_a)
{
}

lambda_p::serialization::result_position::~result_position(void)
{
}
