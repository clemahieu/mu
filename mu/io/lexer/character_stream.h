#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class character_stream : public mu::core::node
			{
			public:
                virtual bool operator () (size_t first, size_t size, mu::string & target) = 0;
				virtual char32_t operator () () = 0;
			};
		}
	}
}
