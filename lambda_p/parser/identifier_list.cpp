#include "identifier_list.h"

#include <lambda_p/tokens/token.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/tokens/identifier.h>

#include <sstream>

lambda_p::parser::identifier_list::identifier_list (lambda_p::parser::parser & parser_a, boost::function <void (lambda_p::tokens::identifier *)> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void lambda_p::parser::identifier_list::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::token_ids id (token->token_id ());
	switch (id)
	{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			auto identifier (static_cast <lambda_p::tokens::identifier *> (token));
			target (identifier);
			break;
		case lambda_p::tokens::token_id_divider:
			parser.state.pop ();
			break;
		default:			
			std::wstringstream message;
			message << L"Expecting complex identifier, identifier, or divider when parsing identifier list, have:";
			message << parser.token_type_name (token);			
			parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
			break;
	}
}