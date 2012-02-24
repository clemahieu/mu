#pragma once

#include <string>

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class visitor;
			class token
			{
			public:
				virtual std::wstring token_name () = 0;
				virtual void operator () (mu::io::tokens::visitor * visitor_a) = 0;
			};
		}
	}
}
