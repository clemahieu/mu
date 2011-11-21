#include <lambda_p/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/parser/position_set.h>
#include <lambda_p/tokens/token.h>
#include <lambda_p/parser/statement.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/association.h>

#include <boost/bind.hpp>

lambda_p::parser::routine::routine (lambda_p::parser::parser & parser_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters, std::vector <std::wstring> & injected_returns)
	: parsed_routine (false),
	routine_m (new lambda_p::core::routine),
	have_surface (false),
	parser (parser_a)
{
	for (auto i = injected_parameters.begin (); i != injected_parameters.end (); ++i)
	{
		size_t injected_position (routine_m->add_declaration ());
		positions [i->first] = injected_position;
		routine_m->injected_surface->declarations.push_back (injected_position);
		routine_m->injected [injected_position] = i->second;
	}
	for (auto i = injected_returns.begin (); i != injected_returns.end (); ++i)
	{
		size_t injected_position (routine_m->add_declaration ());
		routine_m->injected_surface->references.push_back (injected_position);
		unresolved_references.insert (std::multimap <std::wstring, boost::function <void (size_t)>>::value_type (*i, boost::bind <void> (lambda_p::parser::position_set (routine_m->injected_surface->references, routine_m->injected_surface->references.size () - 1), _1)));
	}
}

void lambda_p::parser::routine::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::token_ids token_id (token->token_id ());
	if (have_surface)
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
				boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::statement (parser, *this));
				parser.state.push (new_state);
				parser (token);
			}
			break;
		case lambda_p::tokens::token_id_routine_end:
			if (unresolved_references.empty ())
			{
				parser.target (routine_m);
				parser.state.pop ();
			}
			else
			{
				std::wstring message;
				for (auto i = unresolved_references.begin (); i != unresolved_references.end (); ++i)
				{
					message.append (L"Unresolved reference: ");
					message.append (i->first);
					message.push_back (L'\n');
				}
				parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message)));
			}
			break;
		default:
			std::wstring message (L"Expecting an identifier as target of statement, have: ");
			message.append (parser.token_type_name (token));
			boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			parser.state.push (new_state);
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
				have_surface = true;
				boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::association (parser, *this, *this));
				parser.state.push (new_state);
				parser (token);
			}
			break;
		case lambda_p::tokens::token_id_routine_end:
			parser.target (routine_m);
			parser.state.pop ();
			break;
		default:
			std::wstring message (L"Expecting an identifier or connector at the beginning of a routine, have: ");
			message.append (parser.token_type_name (token));
			boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			parser.state.push (new_state);
			break;
		}
	}
}

boost::function <void (size_t)> lambda_p::parser::routine::sink_declaration ()
{
	routine_m->surface->declarations.push_back (~0);
	boost::function <void (size_t)> result (boost::bind <void> (lambda_p::parser::position_set (routine_m->surface->declarations, routine_m->surface->declarations.size () - 1), _1));
	return result;
}

boost::function <void (size_t)> lambda_p::parser::routine::sink_argument ()
{
	routine_m->surface->references.push_back (~0);
	boost::function <void (size_t)> result (boost::bind <void> (lambda_p::parser::position_set (routine_m->surface->references, routine_m->surface->references.size () - 1), _1));
	return result;
}