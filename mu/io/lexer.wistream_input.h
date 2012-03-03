#pragma once

#include <mu/io/lexer.character_stream.h>

#include <istream>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class wistream_input : public mu::io::lexer::character_stream
			{
			public:
				wistream_input(std::wistream & source_a);
				wchar_t operator () ();
			private:
				std::wistream & source;
			};
		}
	}
}
