#pragma once

#include <lambda_p/errors/error.h>

namespace lambda_p
{
	namespace errors
	{
		class target_not_bindable : public ::lambda_p::errors::error
		{
		public:
            error_id error_type ();
            void string (::std::wostream & stream);
		};
	}
}

