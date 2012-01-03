#include "values.h"

#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/ast/identifier.h>
#include <lambda_p_serialization/parser/single.h>
#include <lambda_p_serialization/tokens/right_square.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p_serialization/ast/expression.h>
#include <lambda_p_serialization/parser/error.h>

#include <boost/bind.hpp>

lambda_p_serialization::parser::values::values (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::single (parser, target, values_m)));
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::identifier * token)
{
	values_m.push_back (boost::shared_ptr <lambda_p_serialization::ast::node> (new lambda_p_serialization::ast::identifier (token->string)));
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::left_square * token)
{
	parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::values (parser, boost::bind (&lambda_p_serialization::parser::values::subexpression, this, _1))));
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::right_square * token)
{
	parser.state.pop ();
	target (boost::shared_ptr <lambda_p_serialization::ast::expression> (new lambda_p_serialization::ast::expression (values_m)));
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::stream_end * token)
{
	parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::error (std::wstring (L"Unexpected end of stream while parsing expression"))));
}

void lambda_p_serialization::parser::values::subexpression (boost::shared_ptr <lambda_p_serialization::ast::expression> expression)
{
	values_m.push_back (expression);
}