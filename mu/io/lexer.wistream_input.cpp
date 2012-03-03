#include "lexer.wistream_input.h"

mu::io::lexer::wistream_input::wistream_input (std::wistream & source_a)
	: source (source_a)
{
}

wchar_t mu::io::lexer::wistream_input::operator () ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = L'\uffff';
	}
	return result;
}
