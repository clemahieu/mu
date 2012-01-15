#pragma once

#include <lambda_p_io/lexer/character_stream.h>

#include <istream>

namespace lambda_p_repl
{
	class cli_stream : public lambda_p_io::lexer::character_stream
	{
	public:
		cli_stream (std::wistream & source_a);
		wchar_t operator () () override;
		std::wistream & source;
		bool end;
	};
}

