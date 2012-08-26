#pragma once

#include <mu/io/lexer_character_stream.h>
#include <mu/core/types.h>

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
                bool operator () (size_t first, size_t size, mu::string & target) override;
				char32_t operator () () override;
			private:
                std::wistream & source;
			};
		}
	}
}
