#include "builder.h"

#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p_serialization/lexer/character_stream.h>
#include <lambda_p_serialization/lexer/wistream_input.h>
#include <lambda_p_serialization/lexer/error.h>
#include <lambda_p_serialization/parser/error.h>

lambda_p_serialization::builder::builder (std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> keywords_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> & globals_a)
	: parser (boost::bind (&(lambda_p_serialization::parser::routine_vector::operator()), &routines, _1), keywords_a, globals_a),
	lexer (boost::bind (&(lambda_p_serialization::parser::parser::operator()), &parser, _1))
{
}

std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> lambda_p_serialization::builder::keywords ()
{
	std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> result;
	return result;
}

std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> lambda_p_serialization::builder::globals ()
{
	std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> result;
	return result;
}

void lambda_p_serialization::builder::finish ()
{
	lexer (L'\uffff');
}

void lambda_p_serialization::builder::operator () (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source)
{
	wchar_t last_char (L' ');
	while (routines.routines->empty () && last_char != L'\uffff' && !lexer.error () && !parser.error ())
	{
		std::wstring line;
		while (last_char != L'\uffff' && last_char != L'\n')
		{
			last_char = source->operator() ();
			line.push_back (last_char);
		}
		operator () (line);
		if (last_char == L'\n')
		{
			last_char = L' ';
		}
	}
}

void lambda_p_serialization::builder::operator << (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source)
{
	wchar_t last_char (source->operator() ());
	while (last_char != L'\uffff')
	{		
		lexer (last_char);
		last_char = source->operator () ();
	}
}

void lambda_p_serialization::builder::operator () (std::wstring & string)
{
	std::wstringstream stream (string);
	boost::shared_ptr <lambda_p_serialization::lexer::wistream_input> input (new lambda_p_serialization::lexer::wistream_input (stream));
	operator << (input);
}

void lambda_p_serialization::builder::operator () (wchar_t const * string)
{
	std::wstring str (string);
	operator () (str);
}

bool lambda_p_serialization::builder::error ()
{
	bool result (lexer.error () || parser.error ());
	return result;
}

void lambda_p_serialization::builder::error_message (std::wostream & out)
{
	auto lexer_error (lexer.error ());
	if (lexer_error.get () != nullptr)
	{
		out << lexer_error->message;
	}
	auto parser_error (parser.error ());
	if (parser_error.get () != nullptr)
	{
		out << parser_error->message;
	}
}