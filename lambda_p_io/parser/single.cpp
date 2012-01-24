#include "single.h"

#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io/parser/error.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/tokens/left_square.h>
#include <lambda_p_io/tokens/stream_end.h>
#include <lambda_p_io/parser/full.h>
#include <lambda_p_io/tokens/parameters.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

#include <boost/make_shared.hpp>

lambda_p_io::parser::single::single (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_a, lambda_p::context first_a)
	: parser (parser_a),
	target (target_a),
	values (values_a),
	first (first_a)
{
}

void lambda_p_io::parser::single::operator () (lambda_p_io::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::full (parser, target, values, names, first)));
}

void lambda_p_io::parser::single::operator () (lambda_p_io::tokens::identifier * token)
{
	names.push_back (token->string);
}

void lambda_p_io::parser::single::operator () (lambda_p_io::tokens::left_square * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::single::operator () (lambda_p_io::tokens::right_square * token)
{
	parser.state.pop ();
	target (boost::make_shared <lambda_p_io::ast::expression> (lambda_p::context (first.first, parser.context.last), values, names));
}

void lambda_p_io::parser::single::operator () (lambda_p_io::tokens::stream_end * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::single::operator () (lambda_p_io::tokens::parameters * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::single::unexpected_token (lambda_p_io::tokens::token * token)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing individual names: ";
	message << token->token_name ();
	(*parser.errors) (message.str ());
    parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
}