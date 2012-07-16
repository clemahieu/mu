#include <mu/io/lexer/istream_input.h>

mu::io::lexer::istream_input::istream_input (std::istream & source_a)
	: source (source_a)
{
}

char32_t mu::io::lexer::istream_input::operator() ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = L'\uffff';
	}
	return result;
}