#pragma once

#include <lambda_p/lexer/character_stream.h>

#include <istream>

namespace lambda_p
{
	namespace lexer
	{
		class wistream_input : public lambda_p::lexer::character_stream
		{
		public:
			wistream_input(std::wistream & source_a);
			wchar_t operator () ();
		private:
			std::wistream & source;
		};
	}
}

