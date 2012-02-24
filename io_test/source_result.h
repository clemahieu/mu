#pragma once

#include <vector>

namespace mu
{
	namespace io_test
	{
		class source_result
		{
		public:
			void operator () (wchar_t char_a);
			std::vector <wchar_t> results;
		};
	}
}
