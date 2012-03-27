#pragma once

#include <mu/io/tokens/token.h>
#include <mu/io/debugging/hash.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class stream_end : public mu::io::tokens::token
			{
			public:
				mu::io::debugging::hash hash;
				std::wstring token_name () override;
				void operator () (mu::io::tokens::visitor * visitor_a) override;
			};
		}
	}
}