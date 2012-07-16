#pragma once

#include <mu/io/debugging/context.h>
#include <mu/core/types.h>

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
				virtual void operator () (mu::core::errors::error * error) = 0;
				virtual bool operator () () = 0;
                virtual void print (mu::ostream & target) = 0;
                void print (std::wostream & target);
				virtual void operator () (mu::string error);
				virtual void operator () (char32_t const * error);
			};
		}
	}
}
