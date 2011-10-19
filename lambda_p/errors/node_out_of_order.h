#pragma once

#include <lambda_p/errors/error.h>

namespace lambda_p
{
	namespace errors
	{
		class node_out_of_order : public lambda_p::errors::error
		{
		public:
			node_out_of_order (size_t statement_number_a, size_t result_number_a);
            error_id error_type ();
            void string (std::wostream & stream);
			size_t statement_number;
			size_t result_number;
		};
	}
}

