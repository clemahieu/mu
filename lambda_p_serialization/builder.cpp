#include "builder.h"

#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p_serialization/lexer/character_stream.h>
#include <lambda_p_serialization/lexer/wistream_input.h>
#include <lambda_p_serialization/lexer/error.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/ast/expression.h>

lambda_p_serialization::builder::builder ()	
	: analyzer (boost::bind (&lambda_p_serialization::builder::analyzer_output, this, _1)),
	parser (boost::bind (&lambda_p_serialization::builder::parser_output, this, _1)),
	lexer (boost::bind (&lambda_p_serialization::builder::lexer_output, this, _1)),
	source (boost::bind (&lambda_p_serialization::lexer::lexer::operator(), &lexer, _1))
{
}

void lambda_p_serialization::builder::operator () (std::wstring & string)
{
	source (string);
}

void lambda_p_serialization::builder::operator () (wchar_t const * string)
{
	source (string);
}

void lambda_p_serialization::builder::operator () (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source_a)
{
	source (source_a);
}

void lambda_p_serialization::builder::operator << (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source_a)
{
	source (source_a);
}

void lambda_p_serialization::builder::finish ()
{
	lexer (L'\uffff');
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

void lambda_p_serialization::builder::analyzer_output (boost::shared_ptr <lambda_p::core::routine> routine_a)
{
	routines.push_back (routine_a);
}

void lambda_p_serialization::builder::parser_output (boost::shared_ptr <lambda_p_serialization::ast::expression> expression_a)
{
	analyzer (expression_a);
}

void lambda_p_serialization::builder::lexer_output (lambda_p_serialization::tokens::token * token_a)
{
	parser (token_a);
}