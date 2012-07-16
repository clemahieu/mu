#include <mu/repl/data_stream.h>

mu::repl::data_stream::data_stream (mu::string string_a)
	: string (string_a)
{
}

char32_t mu::repl::data_stream::operator () ()
{
	char32_t result (string.get ());
	return result;
}