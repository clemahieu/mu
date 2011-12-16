#include "signature.h"

#include <lambda_p_serialization/tokens/token.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/tokens/identifier.h>

#include <sstream>

lambda_p_serialization::parser::signature::signature (lambda_p_serialization::parser::parser & parser_a, lambda_p_serialization::parser::signature_sink & sink_a)
	: state (lambda_p_serialization::parser::signature_state::local_naming),
	parser (parser_a),
	sink (sink_a)
{
}

void lambda_p_serialization::parser::signature::parse (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p_serialization::tokens::token_id_complex_identifier:
	case lambda_p_serialization::tokens::token_id_identifier:
		{
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			switch (state)
			{
			case lambda_p_serialization::parser::local_naming:
				local_names.push_back (identifier->string);
				break;
			case lambda_p_serialization::parser::full_naming:
				if (full_name.empty ())
				{
					full_name = identifier->string;
				}
				else
				{
					parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (L"Can only have one full name for parameters")));
				}
				break;
			}
		}
		break;
	case lambda_p_serialization::tokens::token_id_divider:
		switch (state)
		{
		case lambda_p_serialization::parser::local_naming:
			state = lambda_p_serialization::parser::full_naming;
			break;
		case lambda_p_serialization::parser::full_naming:
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (L"Not expecting divider, expecting right square or identifier")));
			break;
		}
	case lambda_p_serialization::tokens::token_id_right_square:
		parser.state.pop ();
		parser (token);
		break;
	default:
		std::wstringstream message;
		message << L"In routine signature, unexpected token: ";
		message << token->token_name ();
		parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message.str ())));
		break;
	}
}