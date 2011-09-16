#include "routine_input.h"

#include <boost/bind.hpp>

lambda_p_repl::routine_input::routine_input (void)
	: parser (routines),
	lexer (::boost::bind (&::lambda_p_repl::routine_input::token_sink, this, _1))
{
}

lambda_p_repl::routine_input::~routine_input (void)
{
}

void lambda_p_repl::routine_input::operator () (::std::wistream & input_stream, ::std::wostream & output_stream)
{	
	while (routines.routines->empty () && !input_stream.eof () && !lexer.error () && !parser.error ())
	{
		::std::wstring input;
		output_stream << L"lp> ";
		::std::getline (input_stream, input);
		input.push_back ('\n');
		operator () (input);
	}
}

void lambda_p_repl::routine_input::operator () (wchar_t character)
{
	lexer (character);
}

void lambda_p_repl::routine_input::operator() (::std::wstring & string)
{
	for (::std::wstring::const_iterator i = string.begin (); i != string.end (); ++i)
	{
		operator () (*i);
	}
}

void lambda_p_repl::routine_input::error_message (::std::wstring & message)
{
	if (lexer.error ())
	{
		lexer.error_message (message);
	}
	if (parser.error ())
	{
		parser.error_message (message);
	}
}

bool lambda_p_repl::routine_input::error ()
{
	bool result (lexer.error () || parser.error ());
	return result;
}

void lambda_p_repl::routine_input::token_sink (::lambda_p::tokens::token * token)
{
	parser (token);
}