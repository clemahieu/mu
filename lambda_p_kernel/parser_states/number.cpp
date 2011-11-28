#include "number.h"

#include <lambda_p/parser/error.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p_kernel/number_binder.h>
#include <lambda_p_kernel/number.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/errors/error.h>
#include <lambda_p/parser/association_target.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/core/routine.h>

#include <sstream>

lambda_p_kernel::parser_states::number::number (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target_a)
	: parser (parser_a),
	routine (routine_a),
	target (target_a)
{
}

void lambda_p_kernel::parser_states::number::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::identifier * identifier (dynamic_cast <lambda_p::tokens::identifier *> (token));
	if (identifier != nullptr)
	{
		lambda_p_kernel::number_binder binder;
		boost::shared_ptr <lambda_p_kernel::number> number;
		lambda_p::errors::error_list errors;
		binder.core (identifier->string, number, errors);
		if (number.get () != nullptr)
		{
			auto location (target.sink_argument ());
			size_t declaration (routine.routine_m->inject_declaration (number));
			location (declaration);
			parser.state.pop ();
		}
		else
		{
			std::wstringstream message;
			errors.errors [0]->string (message);
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message.str ()));
			parser.state.push (new_state);			
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Expecting identifier while parsing number, have: ";
		message << parser.token_type_name (token);
		boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message.str ()));
		parser.state.push (new_state);
	}
}