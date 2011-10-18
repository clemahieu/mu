#pragma once

#include <lambda_p_repl/character_stream.h>

#include <string>
#include <sstream>

namespace lambda_p_repl
{
	class data_stream : public ::lambda_p_repl::character_stream
	{
	public:
		data_stream (::std::wstring string_a);
		wchar_t operator () ();
		::std::wstringstream string;
	};
}

