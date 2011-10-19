#pragma once

#include <lambda_p/errors/binder_error.h>

namespace lambda_p
{
	namespace errors
	{
		class unexpected_argument_count : public lambda_p::errors::binder_error
		{
		public:
			unexpected_argument_count (std::wstring binder_name_a, size_t actual_a, size_t expected_a);
            error_id error_type ();
            void string (std::wostream & stream);
			size_t actual;
			size_t expected;
		};
	}
}
