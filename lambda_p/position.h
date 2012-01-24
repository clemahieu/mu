#pragma once

namespace lambda_p
{
	class position
	{
	public:
		position ();
		position (size_t row_a, size_t column_a, size_t character_a);
		size_t row;
		size_t column;
		size_t character;
	};
}

