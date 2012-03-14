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
				string_error (std::wstring message_a);
				void string (std::wostream & stream) override;
				std::wstring message;
			};
		}
	}
}
