#include <lambda_p/parser/parser.h>

#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/tokens/divider.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/parser/begin.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/parser/statement.h>
#include <lambda_p/parser/data.h>
#include <lambda_p/parser/finished.h>
#include <lambda_p/parser/association.h>
#include <lambda_p/parser/declaration_location.h>

#include <map>

lambda_p::parser::parser::parser (boost::function <void (boost::shared_ptr < lambda_p::core::routine>)> target_a)
	: target (target_a)
{
	reset ();
}

void lambda_p::parser::parser::operator () (lambda_p::tokens::token * token)
{
	parse_internal (token);
}

void lambda_p::parser::parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
    state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::finished));
	state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::begin));
}

bool lambda_p::parser::parser::error ()
{
	bool result;
	if (state.empty ())
	{
		result = true;
	}
	else
	{
		result = state.top ()->state_type () == lambda_p::parser::state_error;
	}
	return result;
}

lambda_p::parser::state_id lambda_p::parser::parser::current_state ()
{
	return state.top ()->state_type ();
}

void lambda_p::parser::parser::error_message (std::wstring & target)
{
	boost::shared_ptr < lambda_p::parser::error> error_l = (boost::static_pointer_cast < lambda_p::parser::error> (state.top ()));
	target = error_l->message;
}

void lambda_p::parser::parser::parse_internal (lambda_p::tokens::token * token)
{
	lambda_p::parser::state_id state_l (state.top ()->state_type ());
	switch (state_l)
	{
	case lambda_p::parser::state_error:
		parse_error (token);
		break;
	case lambda_p::parser::state_begin:
		parse_begin (token);
		break;
	case lambda_p::parser::state_routine:
		parse_routine (token);
		break;
	case lambda_p::parser::state_statement:
		parse_statement (token);
		break;
	case lambda_p::parser::state_data:
		parse_data (token);
		break;
    case lambda_p::parser::state_finished:
        parse_finished (token);
        break;
	case lambda_p::parser::state_association:
		parse_association (token);
		break;
	default:
		assert (false);
	}
}

void lambda_p::parser::parser::parse_finished (lambda_p::tokens::token * token)
{
    std::wstring message (L"Token received after parser is finished");
    state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::error (message)));
}

void lambda_p::parser::parser::parse_error (lambda_p::tokens::token * token)
{
	// Do nothing in error state, remain in this state
}

void lambda_p::parser::parser::parse_begin (lambda_p::tokens::token * token)
{
	lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
        case lambda_p::tokens::token_id_identifier:
        case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_divider:
        {
            boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::routine);
            state.push (new_state);
            parse_internal (token);
        }
        break;
	case lambda_p::tokens::token_id_stream_end:
		state.pop ();
		break;
	default:
        {
            std::wstring message (L"At top level, expecting identifier or end of stream");
            state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::error (message)));
        }
		break;
	}
}

void lambda_p::parser::parser::parse_routine (lambda_p::tokens::token * token)
{
	boost::shared_ptr < lambda_p::parser::routine> state_l (boost::static_pointer_cast < lambda_p::parser::routine> (state.top ()));
	lambda_p::tokens::token_ids token_id (token->token_id ());
	if (state_l->have_surface)
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
				boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::statement (state_l));
				state.push (new_state);
				parse_internal (token);
			}
			break;
		case lambda_p::tokens::token_id_routine_end:
			if (state_l->unresolved_references.empty ())
			{
				target (state_l->routine_m);
				state.pop ();
			}
			else
			{
				std::wstring message;
				for (std::multimap < std::wstring, declaration_location>::iterator i = state_l->unresolved_references.begin (); i != state_l->unresolved_references.end (); ++i)
				{
					message.append (L"Unresolved reference: ");
					message.append (i->first);
					message.push_back (L'\n');
				}
				state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::error (message)));
			}
			break;
		default:
			std::wstring message (L"Expecting an identifier as target of statement, have: ");
			message.append (token_type_name (token));
			boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
	else
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
		case lambda_p::tokens::token_id_divider:
			{
				state_l->have_surface = true;
				boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::association (state_l, state_l));
				state.push (new_state);
				parse_internal (token);
			}
			break;
		case lambda_p::tokens::token_id_routine_end:
			target (state_l->routine_m);
			state.pop ();
			break;
		default:
			std::wstring message (L"Expecting an identifier or connector at the beginning of a routine, have: ");
			message.append (token_type_name (token));
			boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
}

void lambda_p::parser::parser::parse_statement (lambda_p::tokens::token * token)
{				
	boost::shared_ptr < lambda_p::parser::statement> state_l (boost::static_pointer_cast < lambda_p::parser::statement> (state.top ()));
	if (state_l->have_target)
	{
		state.pop ();
		parse_internal (token);
	} 
	else
	{
		lambda_p::tokens::token_ids token_id (token->token_id ());
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
                state_l->have_target = true;
				lambda_p::tokens::identifier * identifier (static_cast < lambda_p::tokens::identifier *> (token));
				std::map < std::wstring, size_t>::iterator i = state_l->routine->positions.find (identifier->string);
				if (i != state_l->routine->positions.end ())
				{
					assert (state_l->statement_m->target.size () == 0);
					state_l->statement_m->target.push_back (i->second);
				}
				else
				{
					state_l->statement_m->target.push_back (~0);
					state_l->routine->unresolved_references.insert (std::multimap < std::wstring, declaration_location>::value_type (identifier->string, lambda_p::parser::declaration_location (state_l->statement_m->target, 0)));
				}
				state.push (boost::shared_ptr < lambda_p::parser::state> (new lambda_p::parser::association (state_l->routine, state_l)));
			}
			break;
		default:
			std::wstring message (L"Looking for identifier while parsing target of statement");
			boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
}

void lambda_p::parser::parser::parse_association (lambda_p::tokens::token * token)
{	
	boost::shared_ptr <lambda_p::parser::association> state_l (boost::static_pointer_cast < lambda_p::parser::association> (state.top ()));
	lambda_p::tokens::token_ids token_id (token->token_id ());
	if (state_l->on_results)
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
				lambda_p::tokens::identifier * identifier (static_cast < lambda_p::tokens::identifier *> (token));
				std::map < std::wstring, size_t>::iterator i = state_l->routine->positions.find (identifier->string);
				if (i == state_l->routine->positions.end ())
				{
					declaration_location location (state_l->target->sink_declaration ());
					size_t declaration (state_l->routine->routine_m->add_declaration ());
					location.vector [location.index] = declaration;
					state_l->routine->positions [identifier->string] = declaration;
					for (std::multimap <std::wstring, declaration_location>::iterator i = state_l->routine->unresolved_references.find (identifier->string); i != state_l->routine->unresolved_references.end (); ++i)
					{
						i->second.vector [i->second.index] = declaration;
					}
					state_l->routine->unresolved_references.erase (identifier->string);
				}
				else
				{
					std::wstring message (L"Identifier already used: ");
					message.append (identifier->string);
					boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
					state.push (new_state);
				}
			}
			break;
		case lambda_p::tokens::token_id_divider:
            state.pop ();
			break;
		default:
			std::wstring message (L"Looking for identifiers while parsing statement results");
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
	else
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
				lambda_p::tokens::identifier * identifier (static_cast <lambda_p::tokens::identifier *> (token));
				std::map < std::wstring, size_t>::iterator i = state_l->routine->positions.find (identifier->string);
				declaration_location location (state_l->target->sink_argument ());
				if (i != state_l->routine->positions.end ())
				{
					location.vector [location.index] = i->second;
				}
				else
				{
					state_l->routine->unresolved_references.insert (std::multimap <std::wstring, declaration_location>::value_type (identifier->string, location));
				}
			}
			break;
		case lambda_p::tokens::token_id_data:
			{
				boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::data (state_l->routine, state_l));
				state.push (new_state);
			}
			break;
		case lambda_p::tokens::token_id_divider:			
			state_l->on_results = true;
			break;
		default:
			std::wstring message (L"Invalid statement argument: ");
			message.append (token_type_name (token));
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			state.push (new_state);
			break;
		}
	}
}

void lambda_p::parser::parser::parse_data (lambda_p::tokens::token * token)
{
	boost::shared_ptr <lambda_p::parser::data> state_l (boost::static_pointer_cast <lambda_p::parser::data> (state.top ()));
	lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p::tokens::token_id_complex_identifier:
	case lambda_p::tokens::token_id_identifier:
		{
			lambda_p::tokens::identifier * data_string (static_cast <lambda_p::tokens::identifier *> (token));
			declaration_location location (state_l->target->sink_data ());
			size_t declaration (state_l->routine->routine_m->add_data (data_string->string));
			location.vector [location.index] = declaration;
			state.pop ();
		}
		break;
	default:
		std::wstring message (L"Expecting identifier while parsing data, have: ");
		message.append (token_type_name (token));
		boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
		state.push (new_state);
		break;
	}
}

std::wstring lambda_p::parser::parser::token_type_name (lambda_p::tokens::token * token)
{
	std::wstring result;
	size_t token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p::tokens::token_id_complex_identifier:
		result.append (L"complex_identifier");
		break;
	case lambda_p::tokens::token_id_identifier:
		result.append (L"identifier");
		break;
	case lambda_p::tokens::token_id_routine_end:
		result.append (L"routine_end");
		break;
	case lambda_p::tokens::token_id_data:
		result.append (L"data");
		break;
	case lambda_p::tokens::token_id_divider:
		result.append (L"divider");
		break;
	case lambda_p::tokens::token_id_stream_end:
		result.append (L"stream_end");
		break;
	default:
		result.append (L"Unknown");
		assert (false);
	}

	return result;
}