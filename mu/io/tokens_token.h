#pragma once

#include <mu/core/types.h>
#include <mu/io/context.h>

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
                token (mu::io::context const & context_a);
                mu::io::context context;
				virtual mu::string token_name () const = 0;
				virtual void operator () (mu::io::tokens::visitor * visitor_a) = 0;
			};
		}
	}
}
