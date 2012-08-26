#pragma once

#include <mu/io/lexer_character_stream.h>

#include <string>
#include <sstream>

namespace mu
{
	namespace repl
	{
		class data_stream : public mu::io::lexer::character_stream
		{
		public:
			data_stream (mu::string string_a);
			char32_t operator () ();
			mu::stringstream string;
		};
	}
}
