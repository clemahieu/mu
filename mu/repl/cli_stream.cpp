#include "cli_stream.h"

mu::repl::cli_stream::cli_stream (std::wistream & source_a)
	: source (source_a),
	end (false)
{
}

char32_t mu::repl::cli_stream::operator () ()
{	
	wchar_t result (source.get ());
	if (result == L'\n')
	{
		end = true;
	}
	if (source.eof () || end)
	{
		result = L'\uffff';
	}
	return result;
}