#include "wistream_input.h"

lambda_p_io::lexer::wistream_input::wistream_input (std::wistream & source_a)
	: source (source_a)
{
}

wchar_t lambda_p_io::lexer::wistream_input::operator () ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = L'\uffff';
	}
	return result;
}