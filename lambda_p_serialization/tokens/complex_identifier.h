#pragma once

#include <lambda_p/tokens/identifier.h>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class complex_identifier : public identifier
		{
		public:
			complex_identifier (std::wstring identifier_a, std::wstring terminator_a);
			std::wstring terminator;
			token_ids token_id () override;
			std::wstring token_name () override;
		};
	}
}

