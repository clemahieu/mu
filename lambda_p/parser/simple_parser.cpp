#include <lambda_p/parser/simple_parser.h>

lambda_p::parser::simple_parser::simple_parser (::boost::function <void (::boost::shared_ptr < ::lambda_p::core::routine>)> target_a)
	: target (target_a)
{
	reset ();
}

void lambda_p::parser::simple_parser::operator () (::lambda_p::tokens::token * token)
{
	parse_internal (token);
}

void lambda_p::parser::simple_parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (::boost::shared_ptr < ::lambda_p::parser::state> (new ::lambda_p::parser::begin));
}

bool lambda_p::parser::simple_parser::error ()
{
	bool result (state.top ()->state_type () == ::lambda_p::parser::state_error);
	return result;
}

::lambda_p::parser::state_id lambda_p::parser::simple_parser::current_state ()
{
	return state.top ()->state_type ();
}

void lambda_p::parser::simple_parser::error_message (::std::wstring & target)
{
	::boost::shared_ptr < ::lambda_p::parser::error> error_l = (::boost::static_pointer_cast < ::lambda_p::parser::error> (state.top ()));
	target = error_l->message;
}

void lambda_p::parser::simple_parser::parse_internal (::lambda_p::tokens::token * token)
{
	::lambda_p::parser::state_id state_l (state.top ()->state_type ());
	switch (state_l)
	{
	case ::lambda_p::parser::state_error:
		parse_error (token);
		break;
	case ::lambda_p::parser::state_begin:
		parse_begin (token);
		break;
	case ::lambda_p::parser::state_routine:
		parse_routine (token);
		break;
	case ::lambda_p::parser::state_routine_parameter:
		parse_routine_parameters (token);
		break;
	case ::lambda_p::parser::state_body:
		parse_routine_body (token);
		break;
	case ::lambda_p::parser::state_statement:
		parse_statement (token);
		break;
	case ::lambda_p::parser::state_result_ref:
		parse_reference (token);
		break;
	case ::lambda_p::parser::state_data:
		parse_data (token);
		break;
	case ::lambda_p::parser::state_declaration:
		parse_declaration (token);
		break;
	default:
		assert (false);
	}
}

void lambda_p::parser::simple_parser::parse_error (::lambda_p::tokens::token * token)
{
	// Do nothing in error state, remain in this state
}

void lambda_p::parser::simple_parser::parse_begin (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::routine);
	state.push (new_state);
	parse_internal (token);
}

void lambda_p::parser::simple_parser::parse_routine (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::routine> state_l (::boost::static_pointer_cast < ::lambda_p::parser::routine> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	if (!state_l->parsed_routine)
	{
		state_l->parsed_routine = true;
		switch (token_id)
		{
		case ::lambda_p::tokens::token_id_complex_identifier:
		case ::lambda_p::tokens::token_id_identifier:
			{
				::lambda_p::tokens::identifier * routine_name (static_cast < ::lambda_p::tokens::identifier *> (token));
				::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::routine_parameter (state_l, routine_name->string));
				state.push (new_state);
			}
			break;
		default:
			::std::wstring message (L"Expecting an identifier at the beginning of a routine, have: ");
			message.append (token_type_name (token));
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
	else
	{
		switch (token_id)
		{
		case ::lambda_p::tokens::token_id_routine_end:
			state.pop ();
			break;
		default:
			assert (false); // We shouldn't have any token except a routine_end after parsing a routine
			break;
		}
	}
}

void lambda_p::parser::simple_parser::parse_routine_parameters (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::routine_parameter> state_l (::boost::static_pointer_cast < ::lambda_p::parser::routine_parameter> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
	case ::lambda_p::tokens::token_id_identifier:
		{
			::lambda_p::tokens::identifier * parameter_name (static_cast < ::lambda_p::tokens::identifier *> (token));
			size_t position (state_l->positions.size ());
			state_l->positions [parameter_name->string] = position;
		}
		break;
	case ::lambda_p::tokens::token_id_statement_end:
		{
			state_l->routine->routine_m->parameters = state_l->positions.size ();
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::body (state_l->routine, state_l->routine_name, state_l->positions));
			state.pop ();
			state.push (new_state);
		}
		break;
	default:
		::std::wstring message (L"Expecting an identifier or statement_end in routine parameters, have: ");
		message.append (token_type_name (token));
		::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
		state.push (new_state);
		break;
	}
}

void lambda_p::parser::simple_parser::parse_routine_body (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::body> state_l (::boost::static_pointer_cast < ::lambda_p::parser::body> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
	case ::lambda_p::tokens::token_id_identifier:
		{
			::lambda_p::tokens::identifier * statement_name (static_cast < ::lambda_p::tokens::identifier *> (token));
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::statement (state_l, statement_name->string));
			state.push (new_state);
		}
		break;
	case ::lambda_p::tokens::token_id_routine_end:
		target (state_l->routine ());
		state.pop ();
		parse_internal (token);
		break;
	default:
		::std::wstring message (L"Error while parsing routine body, expecting identifier or routine_end, have: ");
		message.append (token_type_name (token));
		::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
		state.push (new_state);
		break;
	}
}

void lambda_p::parser::simple_parser::parse_statement (::lambda_p::tokens::token * token)
{				
	::boost::shared_ptr < ::lambda_p::parser::statement> state_l (::boost::static_pointer_cast < ::lambda_p::parser::statement> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	if (!state_l->have_target)
	{
		switch (token_id)
		{
		case ::lambda_p::tokens::token_id_complex_identifier:
		case ::lambda_p::tokens::token_id_identifier:
			{
				::lambda_p::tokens::identifier * target_statement (static_cast < ::lambda_p::tokens::identifier *> (token));
				::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::reference (target_statement->string));
				state.push (new_state);
				state_l->have_target = true;
				break;
			}
			break;
		default:
			::std::wstring message (L"Error while parsing statement, expecting identifier for target, have: ");
			message.append (token_type_name (token));
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
	else
	{
		switch (token_id)
		{
		case ::lambda_p::tokens::token_id_complex_identifier:
		case ::lambda_p::tokens::token_id_identifier:
			{
				::lambda_p::tokens::identifier * target_statement (static_cast < ::lambda_p::tokens::identifier *> (token));
				::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::reference (target_statement->string));
				state.push (new_state);
			}
			break;
		case ::lambda_p::tokens::token_id_data_token:
			{
				::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::data (state_l));
				state.push (new_state);
			}
			break;
		case ::lambda_p::tokens::token_id_declaration:
			{
				::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::declaration (state_l));
				state.push (new_state);
			}
			break;
		case ::lambda_p::tokens::token_id_statement_end:
			{							
				state.pop ();
			}
			break;
		default:
			::std::wstring message (L"Invalid statement argument: ");
			message.append (token_type_name (token));
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
}

void lambda_p::parser::simple_parser::parse_reference (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::reference> state_l (::boost::static_pointer_cast < ::lambda_p::parser::reference> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
	case ::lambda_p::tokens::token_id_identifier:
		{
			state.pop ();
			::lambda_p::tokens::identifier * target_argument (static_cast < ::lambda_p::tokens::identifier *> (token));
			::lambda_p::parser::reference_identifiers reference (state_l->target_statement, target_argument->string);
			state.top ()->sink_reference (*this, reference);
		}
		break;
	default:
		::std::wstring message (L"Trying to parse a result_ref, expecting an identifier, have: ");
		message.append (token_type_name (token));
		::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
		state.push (new_state);
		break;
	}
}

void lambda_p::parser::simple_parser::parse_data (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::data> state_l (::boost::static_pointer_cast < ::lambda_p::parser::data> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
	case ::lambda_p::tokens::token_id_identifier:
		{
			::lambda_p::tokens::identifier * data_string (static_cast < ::lambda_p::tokens::identifier *> (token));
			state.pop ();
			state.top ()->sink_data (*this, data_string);
		}
		break;
	default:
		::std::wstring message (L"Expecting identifier while parsing data, have: ");
		message.append (token_type_name (token));
		::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
		state.push (new_state);
		break;
	}
}

void lambda_p::parser::simple_parser::parse_declaration (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::declaration> state_l (::boost::static_pointer_cast < ::lambda_p::parser::declaration> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
	case ::lambda_p::tokens::token_id_identifier:
		{
			::lambda_p::tokens::identifier * argument_name (static_cast < ::lambda_p::tokens::identifier *> (token));
			state.pop ();
			state.top () ->sink_declaration (*this, argument_name);
		}
		break;
	default:
		::std::wstring message (L"Expecting identifier while parsing declaration, have: ");
		message.append (token_type_name (token));
		::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
		state.push (new_state);
		break;
	}
}

::std::wstring lambda_p::parser::simple_parser::token_type_name (::lambda_p::tokens::token * token)
{
	::std::wstring result;
	size_t token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
		result.append (L"complex_identifier");
		break;
	case ::lambda_p::tokens::token_id_declaration:
		result.append (L"declaration");
		break;
	case ::lambda_p::tokens::token_id_identifier:
		result.append (L"identifier");
		break;
	case ::lambda_p::tokens::token_id_routine_end:
		result.append (L"routine_end");
		break;
	case ::lambda_p::tokens::token_id_data_token:
		result.append (L"data_token");
		break;
	case ::lambda_p::tokens::token_id_statement_end:
		result.append (L"statement_end");
		break;
	default:
		result.append (L"Unknown");
		assert (false);
	}

	return result;
}