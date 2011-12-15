#include "expression.h"

#include <lambda_p_serialization/tokens/token.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/routine.h>
#include <lambda_p/core/list.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p/core/list_iterator.h>

#include <sstream>

#include <boost/bind.hpp>

lambda_p_serialization::parser::expression::expression (lambda_p_serialization::parser::parser & parser_a, lambda_p_serialization::parser::routine & routine_a, boost::shared_ptr <lambda_p::core::list> list_a)
	: list (list_a),
	parser (parser_a),
	routine (routine_a),
	state (lambda_p_serialization::parser::expression_state::expressions)
{
}
			
void lambda_p_serialization::parser::expression::parse (lambda_p_serialization::tokens::token * token)
{	
	auto self (boost::static_pointer_cast <lambda_p_serialization::parser::expression> (parser.state.top ()));
	switch (state)
	{
	case lambda_p_serialization::parser::expression_state::expressions:
		parse_expression (token);
		break;
	case lambda_p_serialization::parser::expression_state::local_naming:
		parse_local_name (token);
		break;
	case lambda_p_serialization::parser::expression_state::full_naming:
		parse_full_name (token);
		break;
	case lambda_p_serialization::parser::expression_state::nested:
		parse_nested (token);
		break;
	}
}

void lambda_p_serialization::parser::expression::parse_nested (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p_serialization::tokens::token_id_right_square:
		state = lambda_p_serialization::parser::expression_state::expressions;
		break;
	default:
		assert (false);
	}
}

void lambda_p_serialization::parser::expression::parse_expression (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p_serialization::tokens::token_id_divider:
		state = lambda_p_serialization::parser::expression_state::local_naming;
		break;
	case lambda_p_serialization::tokens::token_id_complex_identifier:
	case lambda_p_serialization::tokens::token_id_identifier:
		{
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			auto existing (routine.names.find (identifier->string));
			if (existing != routine.names.end ())
			{
				list->contents.push_back (existing->second);
			}
			else
			{
				auto self (boost::static_pointer_cast <lambda_p_serialization::parser::expression> (parser.state.top ()));
				list->contents.push_back (boost::shared_ptr <lambda_p::core::expression> ());
				routine.unresolved_references.insert (std::multimap <std::wstring, std::pair <boost::shared_ptr <lambda_p_serialization::parser::expression>, size_t>>::value_type (identifier->string, std::pair <boost::shared_ptr <lambda_p::parser::expression>, size_t> (self, list->contents.size () - 1)));
			}
		}
		break;
	case lambda_p_serialization::tokens::token_id_left_square:
		{
			auto new_expression (boost::shared_ptr <lambda_p::core::list> (new lambda_p::core::list));
			list->contents.push_back (new_expression);
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::expression> (new lambda_p_serialization::parser::expression (parser, routine, new_expression)));
		}
		break;
	case lambda_p_serialization::tokens::token_id_right_square:
		if (list->resolved ())
		{
			resolve ();
		}
		parser.state.pop ();
		parser (token);
		break;
	}
}

void lambda_p_serialization::parser::expression::parse_local_name (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p_serialization::tokens::token_id_divider:
		state = lambda_p_serialization::parser::expression_state::full_naming;
		break;
	case lambda_p_serialization::tokens::token_id_complex_identifier:
	case lambda_p_serialization::tokens::token_id_identifier:
		{
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			local_names.push_back (identifier->string);
		}
		break;
	case lambda_p_serialization::tokens::token_id_right_square:
		if (list->resolved ())
		{
			resolve ();
		}
		parser.state.pop ();
		parser (token);
		break;
	}
}

void lambda_p_serialization::parser::expression::parse_full_name (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p_serialization::tokens::token_id_divider:
		{
			std::wstringstream message;
			message << L"Expecting identifier or right bracket while full naming, have divider";				
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message.str ())));
		}
		break;
	case lambda_p_serialization::tokens::token_id_complex_identifier:
	case lambda_p_serialization::tokens::token_id_identifier:
		{
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			if (full_name.empty ())
			{
				full_name = identifier->string;
			}
			else
			{
				std::wstringstream message;
				message << L"Cannot specify more than one full name, have: ";
				message << identifier->string;
				parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message.str ())));
			}
		}
		break;
	case lambda_p_serialization::tokens::token_id_right_square:
		if (list->resolved ())
		{
			resolve ();
		}
		parser.state.pop ();
		parser (token);
		break;
	}
}

void lambda_p_serialization::parser::expression::resolve ()
{
	if (!local_names.empty ())
	{
		auto local_current (local_names.begin ());
		auto local_end (local_names.end ());
		auto list_current (lambda_p::core::list_iterator (list, false));
		auto list_end (lambda_p::core::list_iterator (list, true));
		while (local_current != local_end && list_current != list_end)
		{
			auto identifier (*local_current);
			auto existing (routine.names.find (identifier));
			if (existing == routine.names.end ())
			{
				routine.names.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::core::expression>>::value_type (identifier, *list_current));
				back_resolve (identifier, *list_current);
			}
			else
			{
				std::wstringstream message;
				message << L"Identifier: ";
				message << identifier;
				message << L" has already been defined";
				parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message.str ())));
			}
			++local_current;
			++list_current;
		}
		if ((local_current != local_end) != (list_current != list_end))
		{
			std::wstringstream message;
			message << L"Cardinality of names does not match cardinality of expressions";
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message.str ())));
		}
	}
	if (!full_name.empty ())
	{
		auto existing (routine.names.find (full_name));
		if (existing == routine.names.end ())
		{
			routine.names.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::core::expression>>::value_type (full_name, list));
			back_resolve (full_name, list);
		}
		else
		{
			std::wstringstream message;
			message << L"Identifier: ";
			message << full_name;
			message << L" has already been defined";
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message.str ())));
		}
	}
}

void lambda_p_serialization::parser::expression::back_resolve (std::wstring identifier, boost::shared_ptr <lambda_p::core::expression> expression)
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

void lambda_p_serialization::parser::expression::sink (boost::shared_ptr <lambda_p::core::expression> expression_a)
{
	list->contents.push_back (expression_a);
}