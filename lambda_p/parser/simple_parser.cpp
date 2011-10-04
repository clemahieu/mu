#include <lambda_p/parser/simple_parser.h>

#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/parser/parse_result.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/data.h>
#include <lambda_p/parser/reference_identifiers.h>
#include <lambda_p/core/reference.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/parser/begin.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/parser/statement.h>
#include <lambda_p/parser/data.h>

#include <map>

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
	bool result;
	if (state.empty ())
	{
		result = true;
	}
	else
	{
		result = state.top ()->state_type () == ::lambda_p::parser::state_error;
	}
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
	case ::lambda_p::parser::state_statement:
		parse_statement (token);
		break;
	case ::lambda_p::parser::state_data:
		parse_data (token);
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
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_routine_end:
		state.pop ();
		break;
	default:
		state.push (new_state);
		parse_internal (token);
		break;
	}
}

void lambda_p::parser::simple_parser::parse_routine (::lambda_p::tokens::token * token)
{
	::boost::shared_ptr < ::lambda_p::parser::routine> state_l (::boost::static_pointer_cast < ::lambda_p::parser::routine> (state.top ()));
	::lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
	case ::lambda_p::tokens::token_id_identifier:
		{
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::statement (state_l));
			state.push (new_state);
			parse_internal (token);
		}
		break;
	case ::lambda_p::tokens::token_id_routine_end:
		target (state_l->routine_m);
		state.pop ();
		parse_internal (token);
		break;
	default:
		::std::wstring message (L"Expecting an identifier at the beginning of a routine, have: ");
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
	if (state_l->have_target)
	{
		if (state_l->on_results)
		{
			switch (token_id)
			{
			case ::lambda_p::tokens::token_id_complex_identifier:
			case ::lambda_p::tokens::token_id_identifier:
				{
					::lambda_p::tokens::identifier * identifier (static_cast < ::lambda_p::tokens::identifier *> (token));
					::std::map < ::std::wstring, ::lambda_p::core::declaration *>::iterator i = state_l->routine->positions.find (identifier->string);
					if (i == state_l->routine->positions.end ())
					{
						state_l->routine->positions [identifier->string] = state_l->routine->routine_m->add_declaration ();
					}
					else
					{
						::std::wstring message (L"Identifier already used: ");
						message.append (identifier->string);
						::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
						state.push (new_state);
					}
				}
				break;
			case ::lambda_p::tokens::token_id_connector:
				state_l->on_results = true;
				break;
			default:
				::std::wstring message (L"Looking for identifiers while parsing statement results");
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
					::lambda_p::tokens::identifier * identifier (static_cast < ::lambda_p::tokens::identifier *> (token));
					::std::map < ::std::wstring, ::lambda_p::core::declaration *>::iterator i = state_l->routine->positions.find (identifier->string);
					if (i != state_l->routine->positions.end ())
					{
						state_l->statement_m->target = state_l->routine->routine_m->add_reference (i->second);
					}
					else
					{
						state_l->routine->unresolved_references.insert (::std::multimap < ::std::wstring, ::lambda_p::core::reference *>::value_type (identifier->string, state_l->routine->routine_m->add_reference (NULL)));
					}
				}
				break;
			case ::lambda_p::tokens::token_id_data:
				{
					::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::data (state_l));
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
	else
	{
		switch (token_id)
		{
		case ::lambda_p::tokens::token_id_complex_identifier:
		case ::lambda_p::tokens::token_id_identifier:
			{
				::lambda_p::tokens::identifier * identifier (static_cast < ::lambda_p::tokens::identifier *> (token));
				::std::map < ::std::wstring, ::lambda_p::core::declaration *>::iterator i = state_l->routine->positions.find (identifier->string);
				if (i != state_l->routine->positions.end ())
				{
					state_l->statement_m->target = state_l->routine->routine_m->add_reference (i->second);
				}
				else
				{
					state_l->routine->unresolved_references.insert (::std::multimap < ::std::wstring, ::lambda_p::core::reference *>::value_type (identifier->string, state_l->routine->routine_m->add_reference (NULL)));
				}
			}
			break;
		default:
			::std::wstring message (L"Looking for identifier while parsing target of statement");
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
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
			state_l->statement->statement_m->parameters.push_back (state_l->statement->routine->routine_m->add_data (data_string->string));
			state.pop ();
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

::std::wstring lambda_p::parser::simple_parser::token_type_name (::lambda_p::tokens::token * token)
{
	::std::wstring result;
	size_t token_id (token->token_id ());
	switch (token_id)
	{
	case ::lambda_p::tokens::token_id_complex_identifier:
		result.append (L"complex_identifier");
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