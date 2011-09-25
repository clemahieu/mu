#include <lambda_p/core/position.h>

lambda_p::core::position::position ()
	: statement (-1),
	argument (-1)
{
}

lambda_p::core::position::position (size_t statement_a, size_t argument_a)
	:statement (statement_a),
	argument (argument_a)
{
}

lambda_p::core::position::~position(void)
{
}
