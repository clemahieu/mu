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

#include <boost/bind.hpp>

lambda_p_io::parser::values::values (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::single (parser, target, values_m)));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::identifier * token)
{
	values_m.push_back (boost::shared_ptr <lambda_p_io::ast::node> (new lambda_p_io::ast::identifier (token->string)));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::left_square * token)
{
	parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::values (parser, boost::bind (&lambda_p_io::parser::values::subexpression, this, _1))));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::right_square * token)
{
	parser.state.pop ();
	target (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (values_m)));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::stream_end * token)
{
	parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error (std::wstring (L"Unexpected end of stream while parsing expression"))));
}

void lambda_p_io::parser::values::operator () (lambda_p_io::tokens::parameters * token)
{
	values_m.push_back (boost::shared_ptr <lambda_p_io::ast::parameters> (new lambda_p_io::ast::parameters));
}

void lambda_p_io::parser::values::subexpression (boost::shared_ptr <lambda_p_io::ast::expression> expression)
{
	values_m.push_back (expression);
}