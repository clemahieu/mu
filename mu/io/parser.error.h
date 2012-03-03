#pragma once

#include <mu/io/tokens.visitor.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace parser
		{
			class error : public mu::io::tokens::visitor
			{
			public:
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
			};
		}
	}
}
