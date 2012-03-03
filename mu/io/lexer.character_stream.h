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
				virtual wchar_t operator () () = 0;
			};
		}
	}
}
