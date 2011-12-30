#include "values.h"

#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/ast/identifier.h>

lambda_p_serialization::parser::values::values (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::single (parser, target)));
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::identifier * token)
{
	values_m.push_back (boost::shared_ptr <lambda_p_serialization::ast::node> (new lambda_p_serialization::ast::identifier (token->string)));
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::left_square * token)
{
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::right_square * token)
{
}

void lambda_p_serialization::parser::values::operator () (lambda_p_serialization::tokens::stream_end * token)
{
}