#pragma once

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class association
		{
		public:
            std::vector <size_t> declarations;
			std::vector <size_t> references;
		};
	}
}

