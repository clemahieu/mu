#pragma once

#include <lambda_p_repl/character_stream.h>

#include <sstream>

namespace lambda_p_repl
{
	class wistream_input : public lambda_p_repl::character_stream
	{
	public:
		wistream_input(std::wistream & source_a);
		wchar_t operator () ();
	private:
		std::wistream & source;
	};
}

