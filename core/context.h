#pragma once

#include <core/position.h>

#include <string>

namespace mu
{
	namespace core
	{
		class context
		{
		public:
			context ();
			context (mu::core::position first_a, mu::core::position last_a);
			context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character);
			std::wstring string ();
			bool operator == (mu::core::context const & other);
			mu::core::position first;
			mu::core::position last;
		};
	}
}


