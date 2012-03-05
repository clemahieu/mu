#include "source.h"

#include <mu/io/lexer/character_stream.h>
#include <mu/io/lexer/wistream_input.h>

#include <sstream>

mu::io::source::source (boost::function <void (wchar_t char_a)> target_a)
	: target (target_a)
{
}

void mu::io::source::operator () ()
{
	target (L'\uffff');
}

void mu::io::source::operator () (wchar_t char_a)
{
	target (char_a);
}

void mu::io::source::operator () (boost::shared_ptr <mu::io::lexer::character_stream> source_a)
{
	wchar_t last_char (L' ');
	while (last_char != L'\uffff')
	{
		std::wstring line;
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

void mu::io::source::operator << (boost::shared_ptr <mu::io::lexer::character_stream> source_a)
{
	wchar_t last_char (source_a->operator() ());
	while (last_char != L'\uffff')
	{		
		target (last_char);
		last_char = source_a->operator () ();
	}
}

void mu::io::source::operator () (std::wstring & string)
{
	std::wstringstream stream (string);
	boost::shared_ptr <mu::io::lexer::wistream_input> input (new mu::io::lexer::wistream_input (stream));
	operator << (input);
}

void mu::io::source::operator () (wchar_t const * string)
{
	std::wstring str (string);
	operator () (str);
}