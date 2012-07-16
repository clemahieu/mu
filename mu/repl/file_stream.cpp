#include "file_stream.h"

mu::repl::file_stream::file_stream (std::wstring name_a)
	: input (file)
{
	file.open (std::string (name_a.begin (), name_a.end ()).c_str ());
}

char32_t mu::repl::file_stream::operator () ()
{
	char32_t result (input ());
	return result;
}
