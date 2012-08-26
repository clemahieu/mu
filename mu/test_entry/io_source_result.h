#pragma once

#include <vector>

namespace mu
{
	namespace io_test
	{
		class source_result
		{
		public:
			void operator () (char32_t char_a);
			std::vector <char32_t> results;
		};
	}
}
