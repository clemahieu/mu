#include "cli_stream.h"

lambda_p_repl::cli_stream::cli_stream (std::wistream & source_a)
	: source (source_a),
	end (false)
{
}

wchar_t lambda_p_repl::cli_stream::operator () ()
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