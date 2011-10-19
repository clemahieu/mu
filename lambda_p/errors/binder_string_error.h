#pragma once

#include <lambda_p/errors/binder_error.h>

namespace lambda_p
{
	namespace errors
	{
		class binder_string_error : public lambda_p::errors::binder_error
		{
		public:
			binder_string_error (std::wstring binder_name_a, std::wstring message_a);
			std::wstring message;
            error_id error_type ();
            void string (std::wostream & stream);
		};
	}
}

