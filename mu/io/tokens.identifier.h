#pragma once

#include <iostream>

#include <mu/io/tokens.token.h>

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class identifier : public mu::io::tokens::token
			{	
			public:
				identifier (std::wstring string_a);
				std::wstring token_name () override;
				void operator () (mu::io::tokens::visitor * visitor_a) override;
				std::wstring string;
			};
		}
	}
}
