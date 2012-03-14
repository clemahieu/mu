#pragma once

#include <mu/core/errors/error.h>
#include <mu/io/debugging/context.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class error : public mu::core::errors::error
			{
			public:
				error (boost::shared_ptr <mu::core::errors::error> error_a, mu::io::debugging::context context_a);
				void string (std::wostream & stream) override;
				boost::shared_ptr <mu::core::errors::error> error_m;
				mu::io::debugging::context context;
			};
		}
	}
}