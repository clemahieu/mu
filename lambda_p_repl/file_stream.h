#pragma once

#include <lambda_p_io/lexer/character_stream.h>
#include <lambda_p_io/lexer/istream_input.h>

#include <string>
#include <fstream>

namespace lambda_p_repl
{
	class file_stream : public lambda_p_io::lexer::character_stream
	{
	public:
		file_stream (std::wstring name_a);
		wchar_t operator () ();
		std::fstream file;
		lambda_p_io::lexer::istream_input input;
	};
}

