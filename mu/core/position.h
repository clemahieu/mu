#pragma once

#include <cstring>

namespace mu
{
	namespace core
	{
		class position
		{
		public:
			position ();
			position (size_t row_a, size_t column_a, size_t character_a);
			bool operator == (mu::core::position const & other);
			size_t row;
			size_t column;
			size_t character;
		};
	}
}
