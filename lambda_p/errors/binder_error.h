#pragma once

#include <lambda_p/errors/error.h>

#include <string>

namespace lambda_p
{
	namespace errors
	{
		class binder_error : public lambda_p::errors::error
		{
		public:
			binder_error (std::wstring binder_name_a);
			std::wstring binder_name;
		};
	}
}

