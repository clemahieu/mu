#pragma once

#include <vector>

namespace lambda_p
{
	namespace parser
	{
		class position_set
		{
		public:
			position_set (std::vector <size_t> & target_a, size_t position_a);
			void operator () (size_t declaration_a);
			std::vector <size_t> & target;
			size_t position;
		};
	}
}

