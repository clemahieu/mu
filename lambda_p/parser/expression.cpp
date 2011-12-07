#include "expression.h"

#include <lambda_p/tokens/token.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/core/expression_list.h>
#include <lambda_p/tokens/identifier.h>

#include <sstream>

#include <boost/bind.hpp>

lambda_p::parser::expression::expression (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::core::expression_list * list_a)
	: list (list_a),
	parser (parser_a),
	routine (routine_a),
	state (lambda_p::parser::expression_state::expressions)
{
}
			
void lambda_p::parser::expression::parse (lambda_p::tokens::token * token)
{	
	auto self (boost::static_pointer_cast <lambda_p::parser::expression> (parser.state.top ()));
	lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
		case lambda_p::tokens::token_id_divider:
			switch (state)
			{
			case lambda_p::parser::expression_state::expressions:
				state = lambda_p::parser::expression_state::local_naming;
				break;
			case lambda_p::parser::expression_state::local_naming:
				state = lambda_p::parser::expression_state::full_naming;
				break;
			case lambda_p::parser::expression_state::full_naming:
				{
					std::wstringstream message;
					message << L"Expecting identifier or right bracket while full naming, have divider";				
					parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
				}
				break;
			default:
				assert (false);
			}
			break;
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			auto identifier (static_cast <lambda_p::tokens::identifier *> (token));
			switch (state)
			{
			case lambda_p::parser::expression_state::expressions:
				auto existing (routine.names.find (identifier->string));
				if (existing != routine.names.end ())
				{
					list->contents.push_back (existing->second);
				}
				else
				{
					list->contents.push_back (nullptr);
					routine.unresolved_references.insert (std::multimap <std::wstring, std::pair <boost::shared_ptr <lambda_p::parser::expression>, size_t>>::value_type (identifier->string, std::pair <boost::shared_ptr <lambda_p::parser::expression>, size_t> (self, list->contents.size () - 1)));
				}
				break;
			case lambda_p::parser::expression_state::local_naming:
				local_names.push_back (identifier->string);
				break;
			case lambda_p::parser::expression_state::full_naming:
				if (full_name.empty ())
				{
					full_name = identifier->string;
				}
				else
				{
					std::wstringstream message;
					message << L"Cannot specify more than one full name, have: ";
					message << identifier->string;
					parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
				}
				break;
			}
		case lambda_p::tokens::token_id_left_square:
			auto new_expression (new lambda_p::core::expression_list);
			list->contents.push_back (new_expression);
			parser.state.push (boost::shared_ptr <lambda_p::parser::expression> (new lambda_p::parser::expression (parser, routine, new_expression)));
			break;
		case lambda_p::tokens::token_id_right_square:
			if (list->resolved ())
			{
				resolve ();
			}
			parser.state.pop ();
			break;
		default:
			std::wstringstream message;
			message << L"Unexpected while parsing expression: ";
			message << token->token_name ();
			parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
			break;
	}
}

void lambda_p::parser::expression::resolve ()
{
	if (!local_names.empty ())
	{
		auto local_current (local_names.begin ());
		auto local_end (local_names.end ());
		auto list_current (list->begin ());
		auto list_end (list->end ());
		while (local_current != local_end && list_current != list_end)
		{
			auto identifier (*local_current);
			auto existing (routine.names.find (identifier));
			if (existing == routine.names.end ())
			{
				routine.names.insert (std::map <std::wstring, lambda_p::core::expression *>::value_type (identifier, *list_current));
				back_resolve (identifier, *list_current);
			}
			else
			{
				std::wstringstream message;
				message << L"Identifier: ";
				message << identifier;
				message << L" has already been defined";
				parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
			}
			++local_current;
			++list_current;
		}
		if ((local_current != local_end) != (list_current != list_end))
		{
			std::wstringstream message;
			message << L"Cardinality of names does not match cardinality of expressions";
			parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
		}
	}
	if (!full_name.empty ())
	{
		auto existing (routine.names.find (full_name));
		if (existing == routine.names.end ())
		{
			routine.names.insert (std::map <std::wstring, lambda_p::core::expression *>::value_type (full_name, list));
			back_resolve (full_name, list);
		}
		else
		{
			std::wstringstream message;
			message << L"Identifier: ";
			message << full_name;
			message << L" has already been defined";
			parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
		}
	}
}

void lambda_p::parser::expression::back_resolve (std::wstring identifier, lambda_p::core::expression * expression)
{
	auto unresolved_begin (routine.unresolved_references.find (identifier));
	auto unresolved_end (routine.unresolved_references.end ());
	for (auto unresolved_current (unresolved_begin); unresolved_current != unresolved_end; ++unresolved_current)
	{
		auto update (unresolved_current->second);
		auto list_l (update.first->list);
		assert (!list_l->resolved ());
		list_l->contents [update.second] = expression;
		if (list_l->resolved ())
		{
			update.first->resolve ();
		}
	}
	routine.unresolved_references.erase (unresolved_begin, unresolved_end);
}

void lambda_p::parser::expression::sink (lambda_p::core::expression * expression_a)
{
	list->contents.push_back (expression_a);
}