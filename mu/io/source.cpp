#include <mu/io/source.h>

#include <mu/io/lexer/character_stream.h>
#include <mu/io/lexer/stream_input.h>
#include <mu/io/lexer/context.h>

#include <sstream>

#include <gc_cpp.h>

void mu::io::source::operator () ()
{
	(*this) (U'\U0000FFFF');
}

void mu::io::source::proccess_by_line (mu::io::lexer::character_stream * source_a)
{
	char32_t last_char (U' ');
	while (last_char != U'\U0000FFFF')
	{
		mu::string line;
		while (last_char != U'\U0000FFFF' && last_char != U'\n')
		{
			last_char = (*source_a) ();
			line.push_back (last_char);
		}
		operator () (line);
		if (last_char == U'\n')
		{
			last_char = U' ';
		}
	}
}

void mu::io::source::operator () (mu::io::lexer::character_stream * source_a)
{
    mu::io::lexer::context context;
	context.character = source_a->operator() ();
	while (context.character != U'\U0000FFFF')
	{		
		(*this) (context.character);
		context.character = source_a->operator () ();
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
	operator () (input);    
}

void mu::io::source::operator () (char32_t const * string)
{
	mu::string str (string);
	operator () (str);
}
