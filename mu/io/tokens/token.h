#pragma once

#include <mu/core/types.h>

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
				virtual mu::string token_name () = 0;
				virtual void operator () (mu::io::tokens::visitor * visitor_a) = 0;
			};
		}
	}
}
