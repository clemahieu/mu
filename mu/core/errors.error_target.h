#pragma once

#include <mu/core/context.h>

#include <boost/shared_ptr.hpp>

#include <string>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error;
			class error_target
			{
			public:
				virtual void operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a) = 0;
				virtual bool operator () () = 0;
				virtual void operator () (std::wstring error);
				virtual void operator () (wchar_t const * error);
				void operator () (std::wstring error, mu::core::context context_a);
				void operator () (wchar_t const * error, mu::core::context context_a);
                virtual void print () = 0;
			};
		}
	}
}
