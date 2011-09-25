#pragma once

#include <cstring>

namespace lambda_p
{
	namespace core
	{
		class position
		{
		public:
			position ();
			position (size_t statement_a, size_t argument_a);
			~position (void);
			size_t statement;
			size_t argument;
		};
	}
}

