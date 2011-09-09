#pragma once

#include <cstring>

namespace lambda_p
{
	namespace parser
	{
		class result_position
		{
		public:
			result_position ();
			result_position (size_t statement_a, size_t argument_a);
			~result_position (void);
			size_t statement;
			size_t argument;
		};
	}
}

