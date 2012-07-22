#pragma once

#include <mu/core/errors/error.h>

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
				trace_error (mu::script::values::operation * trace_a, mu::core::errors::error * error_a);
				void string (mu::ostream & stream) override;
				mu::script::values::operation * trace;
				mu::core::errors::error * error;
			};
		}
	}
}