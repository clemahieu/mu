#pragma once

#include <lambda_p/errors/error.h>

namespace lambda_p
{
	namespace errors
	{
		class string_error : public lambda_p::errors::error
		{
		public:
			string_error (std::wstring message_a);
            error_id error_type () override;
            void string (std::wostream & stream) override;
			std::wstring message;
		};
	}
}

