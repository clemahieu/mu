#include "file_stream.h"

mu::repl::file_stream::file_stream (std::wstring name_a)
	: input (file)
{
    file.open (std::string (name_a.begin (), name_a.end ()).c_str ());
}

wchar_t mu::repl::file_stream::operator () ()
{
	wchar_t result (input ());
	return result;
}
