#include "full.h"

#include <io/parser/parser.h>

#include <io/tokens/divider.h>
#include <io/tokens/identifier.h>
#include <io/tokens/left_square.h>
#include <io/tokens/right_square.h>
#include <io/tokens/stream_end.h>
#include <io/parser/error.h>
#include <io/ast/expression.h>
#include <io/tokens/parameters.h>
#include <core/errors/error_target.h>
#include <io/ast/identifier.h>

#include <sstream>

#include <boost/make_shared.hpp>

mu::io::parser::full::full (mu::io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <mu::io::ast::expression>)> target_a, std::vector <boost::shared_ptr <mu::io::ast::node>> values_a, std::vector <boost::shared_ptr <mu::io::ast::identifier>> names_a, mu::core::context first_a)
	: parser (parser_a),
	target (target_a),
	values (values_a),
	names (names_a),
	first (first_a),
	full_name (new mu::io::ast::identifier (mu::core::context (), std::wstring ()))
{
}

void mu::io::parser::full::operator () (mu::io::tokens::divider * token)
{
	unexpected_token (token, parser.context);
}

void mu::io::parser::full::operator () (mu::io::tokens::identifier * token)
{
	if (full_name->string.empty ())
	{
		full_name = boost::make_shared <mu::io::ast::identifier> (parser.context, token->string);
	}
	else
	{		
		std::wstringstream message;
		message << L"Expressions can only have one full name, previously: ";
		message << full_name;
		message << L" current: ";
		message << token->string;
		(*parser.errors) (message.str (), parser.context);
		parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::error));
	}
}

void mu::io::parser::full::operator () (mu::io::tokens::left_square * token)
{
	unexpected_token (token, parser.context);
}

void mu::io::parser::full::operator () (mu::io::tokens::right_square * token)
{
	if (full_name->string.empty ())
	{
		std::wstringstream message;
		message << L"Expression has no full name";
		(*parser.errors) (message.str (), parser.context);
		parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::error));
	}
	else
	{
		parser.state.pop ();
		target (boost::make_shared <mu::io::ast::expression> (mu::core::context (first.first, parser.context.last), values, names, full_name));
	}
}

void mu::io::parser::full::operator () (mu::io::tokens::stream_end * token)
{
	unexpected_token (token, mu::core::context (first.first, parser.context.last));
}

void mu::io::parser::full::operator () (mu::io::tokens::parameters * token)
{
	unexpected_token (token, parser.context);
}

void mu::io::parser::full::unexpected_token (mu::io::tokens::token * token, mu::core::context context_a)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing full name: ";
	message << token->token_name ();
	(*parser.errors) (message.str (), context_a);
    parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::error));
}