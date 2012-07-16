#include <mu/io/source.h>

#include <mu/io/lexer/character_stream.h>
#include <mu/io/lexer/stream_input.h>

#include <sstream>

#include <gc_cpp.h>

void mu::io::source::operator () ()
{
	(*this) (U'\U0000FFFF');
}

void mu::io::source::operator () (mu::io::lexer::character_stream * source_a)
{
	wchar_t last_char (L' ');
	while (last_char != L'\uffff')
	{
		mu::string line;
		while (last_char != L'\uffff' && last_char != L'\n')
		{
			last_char = (*source_a) ();
			line.push_back (last_char);
		}
		operator () (line);
		if (last_char == L'\n')
		{
			last_char = L' ';
		}
	}
}

void mu::io::source::operator << (mu::io::lexer::character_stream * source_a)
{
	wchar_t last_char (source_a->operator() ());
	while (last_char != L'\uffff')
	{		
		(*this) (last_char);
		last_char = source_a->operator () ();
	}
}

void mu::io::source::operator () (mu::string & string)
{
    process_string (string);
}

void mu::io::source::operator ()(mu::string const & string)
{
    process_string (string);
}

void mu::io::source::process_string (mu::string const & string)
{
	mu::stringstream stream (string);
	auto input (new (GC) mu::io::lexer::stream_input (stream));
	operator << (input);    
}

void mu::io::source::operator () (char32_t const * string)
{
	mu::string str (string);
	operator () (str);
}
