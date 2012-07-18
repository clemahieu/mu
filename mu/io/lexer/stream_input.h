#pragma once

#include <mu/io/lexer/character_stream.h>
#include <mu/core/types.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class stream_input : public mu::io::lexer::character_stream
			{
			public:
				stream_input(mu::istream & source_a);
                bool operator () (size_t first, size_t last, mu::string & target) override;
				char32_t operator () () override;
			private:
                mu::istream & source;
			};
		}
	}
}

