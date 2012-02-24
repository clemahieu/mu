#include "single.h"

#include <io/tokens/divider.h>
#include <io/tokens/identifier.h>
#include <io/parser/parser.h>
#include <io/parser/error.h>
#include <io/ast/expression.h>
#include <io/tokens/left_square.h>
#include <io/tokens/stream_end.h>
#include <io/parser/full.h>
#include <io/tokens/parameters.h>
#include <core/errors/error_target.h>
#include <io/ast/identifier.h>

#include <sstream>

#include <boost/make_shared.hpp>

mu::io::parser::single::single (mu::io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <mu::io::ast::expression>)> target_a, std::vector <boost::shared_ptr <mu::io::ast::node>> values_a, mu::core::context first_a)
	: parser (parser_a),
	target (target_a),
	values (values_a),
	first (first_a)
{
}

void mu::io::parser::single::operator () (mu::io::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::full (parser, target, values, names, first)));
}

void mu::io::parser::single::operator () (mu::io::tokens::identifier * token)
{
	names.push_back (boost::make_shared <mu::io::ast::identifier> (parser.context, token->string));
}

void mu::io::parser::single::operator () (mu::io::tokens::left_square * token)
{
	unexpected_token (token, parser.context);
}

void mu::io::parser::single::operator () (mu::io::tokens::right_square * token)
{
	parser.state.pop ();
	target (boost::make_shared <mu::io::ast::expression> (mu::core::context (first.first, parser.context.last), values, names));
}

void mu::io::parser::single::operator () (mu::io::tokens::stream_end * token)
{
	unexpected_token (token, mu::core::context (first.first, parser.context.last));
}

void mu::io::parser::single::operator () (mu::io::tokens::parameters * token)
{
	unexpected_token (token, parser.context);
}

void mu::io::parser::single::unexpected_token (mu::io::tokens::token * token, mu::core::context context_a)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing individual names: ";
	message << token->token_name ();
	(*parser.errors) (message.str (), context_a);
    parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::error));
}