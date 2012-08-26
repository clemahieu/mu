#pragma once

#include <mu/io/tokens/token.h>

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class identifier : public mu::io::tokens::token
			{	
			public:
				identifier (mu::io::context const & context_a, mu::string string_a);
				mu::string token_name () override;
				void operator () (mu::io::tokens::visitor * visitor_a) override;
				mu::string string;
			};
		}
	}
}