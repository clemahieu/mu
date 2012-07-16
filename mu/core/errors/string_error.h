#pragma once

#include <mu/core/errors/error.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class string_error : public mu::core::errors::error
			{
			public:
				string_error (mu::string message_a);
				void string (mu::ostream & stream) override;
				mu::string message;
			};
		}
	}
}
