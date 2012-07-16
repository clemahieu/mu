#include <mu/io/lexer/stream_input.h>

mu::io::lexer::stream_input::stream_input (mu::istream & source_a)
: source (source_a)
{
}

char32_t mu::io::lexer::stream_input::operator () ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = U'\U0000FFFF';
	}
	return result;
}