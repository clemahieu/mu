#pragma once

#include <mu/core/errors/error.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		namespace values
		{
			class operation;
		}
		namespace debugging
		{
			class trace_error : public mu::core::errors::error
			{
			public:				
				trace_error (boost::shared_ptr <mu::script::values::operation> trace_a, boost::shared_ptr <mu::core::errors::error> error_a);
				void string (std::wostream & stream) override;
				boost::shared_ptr <mu::script::values::operation> trace;
				boost::shared_ptr <mu::core::errors::error> error;
			};
		}
	}
}