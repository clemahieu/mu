#pragma once

#include <mu/io/lexer.character_stream.h>
#include <mu/io/lexer.istream_input.h>

#include <string>
#include <fstream>

namespace mu
{
	namespace repl
	{
		class file_stream : public mu::io::lexer::character_stream
		{
		public:
			file_stream (std::wstring name_a);
			wchar_t operator () ();
			std::fstream file;
			mu::io::lexer::istream_input input;
		};
	}
}
