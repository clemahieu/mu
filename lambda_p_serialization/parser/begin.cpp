#include <lambda_p_serialization/parser/begin.h>

#include <lambda_p_serialization/tokens/token.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/parser/values.h>
#include <lambda_p_serialization/tokens/left_square.h>
#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/tokens/right_square.h>

lambda_p_serialization::parser::begin::begin (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p_serialization::parser::begin::operator () (lambda_p_serialization::tokens::divider * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::begin::operator () (lambda_p_serialization::tokens::identifier * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::begin::operator () (lambda_p_serialization::tokens::left_square * token)
{
    boost::shared_ptr <lambda_p_serialization::tokens::visitor> new_state (new lambda_p_serialization::parser::values (parser, target));
    parser.state.push (new_state);
    parser (token);
}

void lambda_p_serialization::parser::begin::operator () (lambda_p_serialization::tokens::right_square * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::begin::operator () (lambda_p_serialization::tokens::stream_end * token)
{
	parser.state.pop ();
}

void lambda_p_serialization::parser::begin::unexpected_token (lambda_p_serialization::tokens::token * token)
{
    std::wstring message (L"At top level, expecting signature or end of stream");
    parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::error (message)));
}