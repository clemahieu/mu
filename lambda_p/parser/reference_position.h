#pragma once

#include <cstring>

namespace lambda_p
{
	namespace parser
	{
		class reference_position
		{
		public:
			reference_position ();
			reference_position (size_t statement_a, size_t argument_a);
			~reference_position (void);
			size_t statement;
			size_t argument;
		};
	}
}

