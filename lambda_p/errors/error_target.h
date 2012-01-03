#pragma once

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
			virtual void operator () (boost::shared_ptr <lambda_p::errors::error> error) = 0;
			virtual bool operator () () = 0;
			void operator () (std::wstring error);
			void operator () (wchar_t const * error);
		};
	}
}

