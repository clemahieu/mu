#pragma once

#include <lambda_p/context.h>

#include <boost/shared_ptr.hpp>

#include <string>

namespace lambda_p
{
	namespace errors
	{
		class error;
		class error_target
		{
		public:
			virtual void operator () (boost::shared_ptr <lambda_p::errors::error> error, lambda_p::context context_a) = 0;
			virtual bool operator () () = 0;
			virtual void operator () (std::wstring error);
			virtual void operator () (wchar_t const * error);
			void operator () (std::wstring error, lambda_p::context context_a);
			void operator () (wchar_t const * error, lambda_p::context context_a);
		};
	}
}

