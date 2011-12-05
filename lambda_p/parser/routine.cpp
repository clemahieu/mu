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
#include <lambda_p/core/expression.h>
#include <lambda_p/parser/expression.h>

#include <boost/bind.hpp>

#include <sstream>

lambda_p::parser::routine::routine (lambda_p::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters, std::vector <std::wstring> & injected_returns)
	: target (target_a),
	parser (parser_a),
	have_surface (false)
{
}

void lambda_p::parser::routine::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::token_ids token_id (token->token_id ());
	if (have_surface)
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_left_square:
			have_surface = false;
			parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::expression (parser, *this, boost::bind <void> (&lambda_p::parser::routine::routine_expression_sink, this, _1))));
			break;
		default:
			std::wstringstream message;
			message << L"Expecting an expression as routine body, have: ";
			message << token->token_name ();
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message.str ()));
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
				boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::identifier_list (parser, boost::bind <void> (&lambda_p::parser::routine::routine_expression_sink, this, _1)));
				parser.state.push (new_state);
				parser (token);
			}
			break;
		case lambda_p::tokens::token_id_stream_end:
			parser.state.pop ();
			break;
		default:
			std::wstringstream message;
			message << L"Expecting an identifier or connector at the beginning of a routine, have: ";
			message << token->token_name ();
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message.str ()));
			parser.state.push (new_state);
			break;
		}
	}
}

void lambda_p::parser::routine::routine_expression_sink (lambda_p::core::expression * expression)
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine (surface, expression));
	surface.clear ();
}
			
void lambda_p::parser::routine::surface_sink (lambda_p::tokens::identifier * identifier)
{
	auto existing (names.find (identifier->string));
	if (existing == names.end ())
	{
		auto expression (new lambda_p::core::expression);
		surface.push_back (expression);
		names.insert (std::map <std::wstring, lambda_p::core::expression *>::value_type (identifier->string, expression));
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