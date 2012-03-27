#include <mu/io/source.h>

#include <mu/io/lexer/character_stream.h>
#include <mu/io/lexer/wistream_input.h>

#include <sstream>

void mu::io::source::operator () ()
{
	(*this) (L'\uffff');
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
		(*this) (last_char);
		last_char = source_a->operator () ();
	}
}

void mu::io::source::operator () (std::wstring & string)
{
    process_string (string);
}

void mu::io::source::operator ()(std::wstring const & string)
{
    process_string (string);
}

void mu::io::source::process_string (std::wstring const & string)
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
