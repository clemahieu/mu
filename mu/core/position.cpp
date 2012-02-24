#include "position.h"

mu::core::position::position ()
	: row (1),
	column (1),
	character (0)
{
}

mu::core::position::position (size_t row_a, size_t column_a, size_t character_a)
	: row (row_a),
	column (column_a),
	character (character_a)
{
}

bool mu::core::position::operator == (mu::core::position const & other)
{
	bool result (row == other.row && column == other.column && character == other.character);
	return result;
}