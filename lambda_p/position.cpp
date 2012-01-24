#include "position.h"

lambda_p::position::position ()
	: row (1),
	column (1),
	character (0)
{
}

lambda_p::position::position (size_t row_a, size_t column_a, size_t character_a)
	: row (row_a),
	column (column_a),
	character (character_a)
{
}
