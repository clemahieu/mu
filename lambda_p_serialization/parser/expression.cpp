#include "expression.h"

#include <lambda_p_serialization/tokens/token.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/routine.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p/core/connection.h>
#include <lambda_p_serialization/parser/reference.h>
#include <lambda_p_serialization/parser/reference_scatter.h>
#include <lambda_p_serialization/parser/reference_tee.h>
#include <lambda_p/core/tee.h>
#include <lambda_p/core/call.h>
#include <lambda_p/core/gather.h>

#include <sstream>

#include <boost/bind.hpp>

lambda_p_serialization::parser::expression::expression (lambda_p_serialization::parser::parser & parser_a, lambda_p_serialization::parser::routine & routine_a, boost::shared_ptr <lambda_p::core::target> target_a)
	: target (target_a),
	tee (new lambda_p::core::tee),
	call (new lambda_p::core::call (tee)),
	gather (new lambda_p::core::gather (call)),
	parser (parser_a),
	routine (routine_a),
	state (lambda_p_serialization::parser::expression_state::expressions),
	position (0)
{
	tee->targets.push_back (target_a);
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
			gather->increment ();
			auto target_l (boost::shared_ptr <lambda_p::core::target> (new lambda_p::core::connection (gather, position)));
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			auto existing (routine.names.find (identifier->string));
			if (existing != routine.names.end ())
			{
				(*existing->second) (target_l);
			}
			else
			{
				routine.unresolved_references.insert (std::multimap <std::wstring, boost::shared_ptr <lambda_p::core::target>>::value_type (identifier->string, target_l));
			}
			++position;
		}
		break;
	case lambda_p_serialization::tokens::token_id_left_square:
		{
			gather->increment ();
			auto target_l (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather, position)));
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::expression> (new lambda_p_serialization::parser::expression (parser, routine, target_l)));
			++position;
		}
		break;
	case lambda_p_serialization::tokens::token_id_right_square:
		resolve ();
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
		resolve ();
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
		resolve ();
		parser.state.pop ();
		parser (token);
		break;
	}
}

void lambda_p_serialization::parser::expression::resolve ()
{
	if (!local_names.empty ())
	{
		size_t position (0);
		for (auto i (local_names.begin ()), j (local_names.end ()); i != j; ++i, ++position)
		{
			routine.add_name (*i, boost::shared_ptr <lambda_p_serialization::parser::reference> (new lambda_p_serialization::parser::reference_scatter (scatter, position)));
		}
	}
	if (!full_name.empty ())
	{
		routine.add_name (full_name, boost::shared_ptr <lambda_p_serialization::parser::reference> (new lambda_p_serialization::parser::reference_tee (tee)));
	}
}