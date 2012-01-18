#include "full.h"

#include <lambda_p_io/parser/parser.h>

#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/left_square.h>
#include <lambda_p_io/tokens/right_square.h>
#include <lambda_p_io/tokens/stream_end.h>
#include <lambda_p_io/parser/error.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/tokens/parameters.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

lambda_p_io::parser::full::full (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_a, std::vector <std::wstring> names_a)
	: parser (parser_a),
	target (target_a),
	values (values_a),
	names (names_a)
{
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::divider * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::identifier * token)
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
		(*parser.errors) (message.str ());
		parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
	}
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::left_square * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::right_square * token)
{
	if (full_name.empty ())
	{
		std::wstringstream message;
		message << L"Expression has no full name";
		(*parser.errors) (message.str ());
		parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
	}
	else
	{
		parser.state.pop ();
		target (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (values, names, full_name)));
	}
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::stream_end * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::parameters * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::full::unexpected_token (lambda_p_io::tokens::token * token)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing full name: ";
	message << token->token_name ();
	(*parser.errors) (message.str ());
    parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
}