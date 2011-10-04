#pragma once

#include <sstream>

namespace lambda_p_repl
{
	class wistream_input
	{
	public:
		wistream_input(::std::wistream & source_a);
		wchar_t operator () ();
	private:
		::std::wistream & source;
	};
}

