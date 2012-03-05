#pragma once

#include <mu/io/tokens/token.h>

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class parameters : public mu::io::tokens::token
			{
			public:
				std::wstring token_name () override;
				void operator () (mu::io::tokens::visitor * visitor_a) override;
			};
		}
	}
}