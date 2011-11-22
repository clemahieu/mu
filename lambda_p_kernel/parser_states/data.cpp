#include "data.h"

#include <lambda_p/tokens/token.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/association_target.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/error.h>

lambda_p_kernel::parser_states::data::data (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target_a)
	: parser (parser_a),
	routine (routine_a),
	target (target_a)
{
}

void lambda_p_kernel::parser_states::data::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p::tokens::token_id_complex_identifier:
	case lambda_p::tokens::token_id_identifier:
		{
			lambda_p::tokens::identifier * data_string (static_cast <lambda_p::tokens::identifier *> (token));
			auto location (target.sink_argument ());
			size_t declaration (routine.routine_m->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (data_string->string))));
			location (declaration);
			parser.state.pop ();
		}
		break;
	default:
		std::wstring message (L"Expecting identifier while parsing data, have: ");
		message.append (parser.token_type_name (token));
		boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
		parser.state.push (new_state);
		break;
	}
}