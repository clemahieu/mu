#pragma once

#include <lambda_p/tokens/identifier.h>

namespace lambda_p
{
	namespace tokens
	{
		class complex_identifier : public identifier
		{
		public:
			complex_identifier (::std::wstring identifier_a, ::std::wstring terminator_a);
			~complex_identifier (void);
			::std::wstring terminator;
		};
	}
}

