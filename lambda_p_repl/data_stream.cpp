#include "data_stream.h"

lambda_p_repl::data_stream::data_stream (::std::wstring string_a)
	: string (string_a)
{
}

wchar_t lambda_p_repl::data_stream::operator () ()
{
	wchar_t result (string.get ());
	return result;
}