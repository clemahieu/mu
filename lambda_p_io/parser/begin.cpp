#include <lambda_p_io/parser/begin.h>

#include <lambda_p_io/tokens/token.h>
#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io/parser/error.h>
#include <lambda_p_io/parser/values.h>
#include <lambda_p_io/tokens/left_square.h>
#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/right_square.h>
#include <lambda_p_io/tokens/parameters.h>
#include <lambda_p/errors/error_target.h>

lambda_p_io::parser::begin::begin (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p_io::parser::begin::operator () (lambda_p_io::tokens::divider * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::begin::operator () (lambda_p_io::tokens::identifier * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::begin::operator () (lambda_p_io::tokens::left_square * token)
{
    boost::shared_ptr <lambda_p_io::tokens::visitor> new_state (new lambda_p_io::parser::values (parser, target));
    parser.state.push (new_state);
}

void lambda_p_io::parser::begin::operator () (lambda_p_io::tokens::right_square * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::begin::operator () (lambda_p_io::tokens::stream_end * token)
{
	parser.state.pop ();
}

void lambda_p_io::parser::begin::operator () (lambda_p_io::tokens::parameters * token)
{
	unexpected_token (token);
}

void lambda_p_io::parser::begin::unexpected_token (lambda_p_io::tokens::token * token)
{
    std::wstring message (L"At top level, expecting signature or end of stream");
	(*parser.errors) (message, parser.context);
    parser.state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::error));
}