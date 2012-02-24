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
#include <core/errors/error_target.h>
#include <lambda_p_io/ast/identifier.h>

#include <sstream>

#include <boost/make_shared.hpp>

lambda_p_io::parser::full::full (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_a, std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> names_a, mu::core::context first_a)
	: parser (parser_a),
	target (target_a),
	values (values_a),
	names (names_a),
	first (first_a),
	full_name (new lambda_p_io::ast::identifier (mu::core::context (), std::wstring ()))
{
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::divider * token)
{
	unexpected_token (token, parser.context);
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::identifier * token)
{
	if (full_name->string.empty ())
	{
		full_name = boost::make_shared <lambda_p_io::ast::identifier> (parser.context, token->string);
	}
	else
	{		
		std::wstringstream message;
		message << L"Expressions can only have one full name, previously: ";
		message << full_name;
		message << L" current: ";
		message << token->string;
		(*parser.errors) (message.str (), parser.context);
		parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
	}
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::left_square * token)
{
	unexpected_token (token, parser.context);
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::right_square * token)
{
	if (full_name->string.empty ())
	{
		std::wstringstream message;
		message << L"Expression has no full name";
		(*parser.errors) (message.str (), parser.context);
		parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
	}
	else
	{
		parser.state.pop ();
		target (boost::make_shared <lambda_p_io::ast::expression> (mu::core::context (first.first, parser.context.last), values, names, full_name));
	}
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::stream_end * token)
{
	unexpected_token (token, mu::core::context (first.first, parser.context.last));
}

void lambda_p_io::parser::full::operator () (lambda_p_io::tokens::parameters * token)
{
	unexpected_token (token, parser.context);
}

void lambda_p_io::parser::full::unexpected_token (lambda_p_io::tokens::token * token, mu::core::context context_a)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing full name: ";
	message << token->token_name ();
	(*parser.errors) (message.str (), context_a);
    parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
}