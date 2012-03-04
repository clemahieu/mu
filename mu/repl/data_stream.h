#pragma once

#include <mu/io/lexer.character_stream.h>

#include <string>
#include <sstream>

namespace mu
{
	namespace repl
	{
		class data_stream : public mu::io::lexer::character_stream
		{
		public:
			data_stream (std::wstring string_a);
			wchar_t operator () ();
			std::wstringstream string;
		};
	}
}
