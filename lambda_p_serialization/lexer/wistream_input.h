#pragma once

#include <lambda_p_serialization/lexer/character_stream.h>

#include <istream>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class wistream_input : public lambda_p_serialization::lexer::character_stream
		{
		public:
			wistream_input(std::wistream & source_a);
			wchar_t operator () ();
		private:
			std::wistream & source;
		};
	}
}

