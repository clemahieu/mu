#pragma once

#include <lambda_p_io/lexer/character_stream.h>

#include <istream>

namespace lambda_p_io
{
	namespace lexer
	{
		class istream_input : public lambda_p_io::lexer::character_stream
		{
		public:
			istream_input (std::istream & source_a);
			wchar_t operator () ();
		private:
			std::istream & source;
		};
	}
}

