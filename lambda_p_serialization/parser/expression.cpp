#include "expression.h"

#include <lambda_p_serialization/tokens/token.h>
#include <lambda_p_serialization/ast/identifier.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/error.h>

#include <sstream>

#include <boost/bind.hpp>

lambda_p_serialization::parser::expression::expression (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target_a)
	: state (lambda_p_serialization::parser::expression_state::values),
	parser (parser_a),
	target (target_a)
{
}

void lambda_p_serialization::parser::expression::parse (lambda_p_serialization::tokens::token * token)
{
	switch (state)
	{
	case lambda_p_serialization::parser::expression_state::values:
		parse_value (token);
		break;
	case lambda_p_serialization::parser::expression_state::individual_names:
		parse_individual_names (token);
		break;
	case lambda_p_serialization::parser::expression_state::full_name:
		parse_full_name (token);
		break;
	}
}

void lambda_p_serialization::parser::expression::parse_value (lambda_p_serialization::tokens::token * token)
{
	auto id (token->token_id ());
	switch (id)
	{
	case lambda_p_serialization::tokens::token_id_complex_identifier:
	case lambda_p_serialization::tokens::token_id_identifier:
		{
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			values.push_back (boost::shared_ptr <lambda_p_serialization::ast::node> (new lambda_p_serialization::ast::identifier (identifier->string)));
		}
		break;
	case lambda_p_serialization::tokens::token_id_divider:
		state = lambda_p_serialization::parser::expression_state::individual_names;
		break;
	case lambda_p_serialization::tokens::token_id_left_square:
		parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::expression> (new lambda_p_serialization::parser::expression (parser, boost::bind <void> (&lambda_p_serialization::parser::expression::subvalue, _1))));
		break;
	default:
		std::wstringstream message;
		message << L"Unexpected token while parsing expression values: ";
		message << token->token_name ();
		parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::error> (new lambda_p_serialization::parser::error (message.str ())));
		break;
	}
}
			
void lambda_p_serialization::parser::expression::subvalue (boost::shared_ptr <lambda_p_serialization::ast::node> value)
{
	assert (state == lambda_p_serialization::parser::expression_state::values);
	values.push_back (value);
}

void lambda_p_serialization::parser::expression::parse_individual_names (lambda_p_serialization::tokens::token * token)
{
	auto id (token->token_id ());
	switch (id)
	{
	case lambda_p_serialization::tokens::token_id_complex_identifier:
	case lambda_p_serialization::tokens::token_id_identifier:
		{
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			individual_names.push_back (identifier->string);
		}
		break;
	default:
		std::wstringstream message;
		message << L"Unexpected token while parsing individual names: ";
		message << token->token_name ();
		parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::error> (new lambda_p_serialization::parser::error (message.str ())));
		break;
	}
}

void lambda_p_serialization::parser::expression::parse_full_name (lambda_p_serialization::tokens::token * token)
{
	auto id (token->token_id ());
	switch (id)
	{
	case lambda_p_serialization::tokens::token_id_complex_identifier:
	case lambda_p_serialization::tokens::token_id_identifier:
		{
			auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
			if (full_name.empty ())
			{
				full_name.assign (identifier->string.begin (), identifier->string.end ());
			}
			else
			{
				std::wstringstream message;
				message << L"More than one full name identifier: ";
				message << identifier->string;
				parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::error> (new lambda_p_serialization::parser::error (message.str ())));
			}
		}
		break;
	default:
		std::wstringstream message;
		message << L"Unexpected token while parsing full name: ";
		message << token->token_name ();
		parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::error> (new lambda_p_serialization::parser::error (message.str ())));
		break;
	}
}