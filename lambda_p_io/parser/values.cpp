#include "values.h"

#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/parser/single.h>
#include <lambda_p_io/tokens/right_square.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/parser/error.h>
#include <lambda_p_io/tokens/parameters.h>
#include <lambda_p_io/ast/parameters.h>
#include <lambda_p/errors/error_target.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

lambda_p_io::parser::values::values (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a)
	: parser (parser_a),
	target (target_a),
	first (parser_a.context)
{
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::make_shared <lambda_p_io::parser::single> (parser, target, values_m));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::identifier * token)
{
	values_m.push_back (boost::make_shared <lambda_p_io::ast::identifier> (parser.context, token->string));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::left_square * token)
{
	parser.state.push (boost::make_shared <lambda_p_io::parser::values> (parser, boost::bind (&lambda_p_io::parser::values::subexpression, this, _1)));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::right_square * token)
{
	parser.state.pop ();
	target (boost::make_shared <lambda_p_io::ast::expression> (lambda_p::context (first.first, parser.context.last), values_m));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::stream_end * token)
{
	(*parser.errors) (L"Unexpected end of stream while parsing expression");
	parser.state.push (boost::make_shared <lambda_p_io::parser::error> ());
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::parameters * token)
{
	values_m.push_back (boost::make_shared <lambda_p_io::ast::parameters> (parser.context));
}

void lambda_p_io::parser::values::subexpression (boost::shared_ptr <lambda_p_io::ast::expression> expression)
{
	values_m.push_back (expression);
}