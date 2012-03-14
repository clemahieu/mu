#pragma once

#include <mu/core/errors/error.h>
#include <mu/core/context.h>

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
				error (boost::shared_ptr <mu::core::errors::error> error_a, mu::core::context context_a);
				void string (std::wostream & stream) override;
				boost::shared_ptr <mu::core::errors::error> error_m;
				mu::core::context context;
			};
		}
	}
}