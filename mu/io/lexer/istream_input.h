#pragma once

#include <mu/io/lexer/character_stream.h>

#include <istream>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class istream_input : public mu::io::lexer::character_stream
			{
			public:
				istream_input (std::istream & source_a);
				char32_t operator () () override;
			private:
				std::istream & source;
			};
		}
	}
}
