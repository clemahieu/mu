#include <mu/io/parser/single.h>

#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/parser/parser.h>
#include <mu/io/parser/error.h>
#include <mu/io/ast/expression.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/parser/full.h>
#include <mu/io/tokens/parameters.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/parser/target.h>

#include <sstream>

#include <boost/make_shared.hpp>

mu::io::parser::single::single (mu::io::parser::parser & parser_a, mu::io::parser::target & target_a, std::vector <boost::shared_ptr <mu::io::ast::node>> values_a, mu::io::debugging::context first_a)
	: parser (parser_a),
	values (values_a),
	first (first_a),
	target (target_a)
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
	unexpected_token (token);
}

void mu::io::parser::single::operator () (mu::io::tokens::right_square * token)
{
	parser.state.pop ();
	target (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (first.first, parser.context.last), values, names));
}

void mu::io::parser::single::operator () (mu::io::tokens::stream_end * token)
{
	unexpected_token (token);
}

void mu::io::parser::single::operator () (mu::io::tokens::parameters * token)
{
	unexpected_token (token);
}

void mu::io::parser::single::unexpected_token (mu::io::tokens::token * token)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing individual names: ";
	message << token->token_name ();
	(*parser.errors) (message.str ());
    parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::error));
}