#include "single.h"

#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/error.h>

#include <sstream>

lambda_p_serialization::parser::single::single (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p_serialization::parser::single::operator () (lambda_p_serialization::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::full (parser, target)));
}

void lambda_p_serialization::parser::single::operator () (lambda_p_serialization::tokens::identifier * token)
{
	names.push_back (token->string);
}

void lambda_p_serialization::parser::single::operator () (lambda_p_serialization::tokens::left_square * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::single::operator () (lambda_p_serialization::tokens::right_square * token)
{
	
}

void lambda_p_serialization::parser::single::operator () (lambda_p_serialization::tokens::stream_end * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::single::unexpected_token (lambda_p_serialization::tokens::token * token)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing individual names: ";
	message << token->token_name ();
    parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::error (message.str ())));
}