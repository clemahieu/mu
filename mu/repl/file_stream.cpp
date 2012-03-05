#include "file_stream.h"

mu::repl::file_stream::file_stream (std::wstring name_a)
	: input (file)
{
	file.open (name_a);
}

wchar_t mu::repl::file_stream::operator () ()
{
	wchar_t result (input ());
	return result;
}
