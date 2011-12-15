#pragma once

#include <lambda_p_serialization/tokens/identifier.h>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class complex_identifier : public identifier
		{
		public:
			complex_identifier (std::wstring identifier_a, std::wstring terminator_a);
			std::wstring terminator;
			lambda_p_serialization::tokens::token_ids token_id () override;
			std::wstring token_name () override;
		};
	}
}

