#pragma once

#include <mu/io/debugging/context.h>

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
                virtual ~error_target ();
				virtual void operator () (boost::shared_ptr <mu::core::errors::error> error) = 0;
				virtual bool operator () () = 0;
                virtual void print (std::wostream & target) = 0;
				virtual void operator () (std::wstring error);
				virtual void operator () (wchar_t const * error);
			};
		}
	}
}
