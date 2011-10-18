#pragma once

#include <lambda_p_repl/character_stream.h>

#include <iostream>

namespace lambda_p_repl
{
	class istream_input
	{
	public:
		istream_input (::std::istream & source_a);
		wchar_t operator () ();
	private:
		::std::istream & source;
	};
}

