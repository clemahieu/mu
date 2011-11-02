#include "builder.h"

#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p/lexer/character_stream.h>
#include <lambda_p/lexer/wistream_input.h>

lambda_p::builder::builder ()
	: parser (boost::bind (&(lambda_p::parser::routine_vector::operator()), &routines, _1), injected_declarations (), injected_references ()),
	lexer (boost::bind (&(lambda_p::parser::parser::operator()), &parser, _1))
{
}

void lambda_p::builder::finish ()
{
	lexer (L'\uffff');
}

void lambda_p::builder::operator << (boost::shared_ptr <lambda_p::lexer::character_stream> source)
{
	wchar_t last_char (source->operator() ());
	while (last_char != L'\uffff')
	{		
		lexer (last_char);
		last_char = source->operator () ();
	}
}

void lambda_p::builder::operator () (std::wstring & string)
{
	std::wstringstream stream (string);
	boost::shared_ptr <lambda_p::lexer::wistream_input> input (new lambda_p::lexer::wistream_input (stream));
	operator << (input);
}

void lambda_p::builder::operator () (wchar_t const * string)
{
	std::wstring str (string);
	operator () (str);
}

std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> lambda_p::builder::injected_declarations ()
{
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> result;
	return result;
}

std::vector <std::wstring> lambda_p::builder::injected_references ()
{
	std::vector <std::wstring> result;
	return result;
}