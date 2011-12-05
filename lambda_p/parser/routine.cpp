#include <lambda_p/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/parser/position_set.h>
#include <lambda_p/tokens/token.h>
#include <lambda_p/parser/statement.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/identifier_list.h>
#include <lambda_p/tokens/identifier.h>

#include <boost/bind.hpp>

#include <sstream>

lambda_p::parser::routine::routine (lambda_p::parser::parser & parser_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters, std::vector <std::wstring> & injected_returns)
	: parsed_routine (false),
	routine_m (new lambda_p::core::routine),
	have_surface (false),
	parser (parser_a)
{
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
				boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::identifier_list (parser, );
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
			
void lambda_p::parser::routine::surface_sink (lambda_p::tokens::identifier * identifier)
{
	auto existing (names.find (identifier->string));
	if (existing == names.end ())
	{
		names.insert (identifier->string, 
	}
	else
	{
		std::wstringstream message;
		message << L"Identifier called: ";
		message << identifier->string;
		message << L" already exists";
		parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
	}
}