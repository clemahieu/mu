#include "full.h"

#include <lambda_p_serialization/parser/parser.h>

#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/tokens/left_square.h>
#include <lambda_p_serialization/tokens/right_square.h>
#include <lambda_p_serialization/tokens/stream_end.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/ast/expression.h>

#include <sstream>

lambda_p_serialization::parser::full::full (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target_a, std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values_a, std::vector <std::wstring> names_a)
	: parser (parser_a),
	target (target_a),
	values (values_a),
	names (names_a)
{
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::divider * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::identifier * token)
{
	if (full_name.empty ())
	{
		full_name = token->string;
	}
	else
	{		
		std::wstringstream message;
		message << L"Expressions can only have one full name, previously: ";
		message << full_name;
		message << L" current: ";
		message << token->string;
		parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::error (message.str ())));
	}
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::left_square * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::right_square * token)
{
	if (full_name.empty ())
	{
		std::wstringstream message;
		message << L"Expression has no full name";
		parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::error (message.str ())));
	}
	else
	{
		parser.state.pop ();
		target (boost::shared_ptr <lambda_p_serialization::ast::expression> (new lambda_p_serialization::ast::expression (values, names, full_name)));
	}
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::stream_end * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::full::unexpected_token (lambda_p_serialization::tokens::token * token)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing full name: ";
	message << token->token_name ();
    parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::error (message.str ())));
}