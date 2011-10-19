#pragma once

#include <lambda_p/errors/error.h>

namespace lambda_p
{
	namespace errors
	{
		class unresolved_statement : public lambda_p::errors::error
		{
		public:
			unresolved_statement (size_t statement_number_a);
            error_id error_type ();
            void string (std::wostream & stream);
			size_t statement_number;
		};
	}
}

