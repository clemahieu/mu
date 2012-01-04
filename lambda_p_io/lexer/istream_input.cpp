#include "istream_input.h"

lambda_p_io::lexer::istream_input::istream_input (std::istream & source_a)
	: source (source_a)
{
}

wchar_t lambda_p_io::lexer::istream_input::operator() ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = L'\uffff';
	}
	return result;
}