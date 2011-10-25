#pragma once

#include <vector>

namespace lambda_p
{
	namespace parser
	{
		class declaration_location
		{
		public:
			declaration_location (std::vector <size_t> & vector_a, size_t index_a);
			std::vector <size_t> & vector;
			size_t index;
		};
	}
}
