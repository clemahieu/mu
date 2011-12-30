#include "full.h"

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::divider * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::identifier * token)
{
	names.push_back (token->string);
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::left_square * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::right_square * token)
{
	
}

void lambda_p_serialization::parser::full::operator () (lambda_p_serialization::tokens::stream_end * token)
{
	unexpected_token (token);
}

void lambda_p_serialization::parser::full::unexpected_token (lambda_p_serialization::tokens::token * token)
{
    std::wstringstream message;
	message << L"Unexpected token while parsing full name: ";
	message << token->token_name ();
    parser.state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::error (message.str ())));
}