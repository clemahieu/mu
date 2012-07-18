#pragma once

#include <mu/io/lexer/character_stream.h>

#include <istream>

namespace mu
{
	namespace repl
	{
		class cli_stream : public mu::io::lexer::character_stream
		{
		public:
			cli_stream (std::wistream & source_a);
            bool operator () (size_t first, size_t last, mu::string & target) override;
			char32_t operator () () override;
			std::wistream & source;
			bool end;
		};
	}
}
