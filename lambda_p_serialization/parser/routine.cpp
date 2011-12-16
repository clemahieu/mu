#include <lambda_p_serialization/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p_serialization/tokens/token.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p/core/expression.h>
#include <lambda_p_serialization/parser/expression.h>

#include <boost/bind.hpp>

#include <sstream>

lambda_p_serialization::parser::routine::routine (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a)
	: target (target_a),
	parser (parser_a),
	state (lambda_p_serialization::parser::routine_state::surface),
	routine_m (new lambda_p::core::routine)
{
}

void lambda_p_serialization::parser::routine::parse (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (state)
	{
	case lambda_p_serialization::parser::routine_state::surface:
		switch (token_id)
		{
		case lambda_p_serialization::tokens::token_id_complex_identifier:
		case lambda_p_serialization::tokens::token_id_identifier:
			{
				auto identifier (static_cast <lambda_p_serialization::tokens::identifier *> (token));
				auto existing (names.find (identifier->string));
				if (existing == names.end ())
				{
					auto expression (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
					routine_m->surface.push_back (expression);
					names.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::core::expression>>::value_type (identifier->string, expression));
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
			break;
		case lambda_p_serialization::tokens::token_id_divider:
			state = lambda_p::parser::routine_state::expression_begin;
			break;
		case lambda_p_serialization::tokens::token_id_stream_end:
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
		break;
	case lambda_p::parser::routine_state::expression_begin:
		switch (token_id)
		{
		case lambda_p::tokens::token_id_left_square:
			state = lambda_p::parser::routine_state::expression_end;
			parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::expression (parser, *this, routine_m->expression)));
			break;
		default:
			std::wstringstream message;
			message << L"Expecting an expression as routine body, have: ";
			message << token->token_name ();
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message.str ()));
			parser.state.push (new_state);
			break;
		}
		break;
	case lambda_p::parser::routine_state::expression_end:
		switch (token_id)
		{
		case lambda_p::tokens::token_id_right_square:
			target (routine_m);
			break;
		default:
			assert (false);
			break;
		}
		break;
	}
}

void lambda_p_serialization::parser::routine::operator () (std::vector <std::wstring> parameters, std::wstring full_parameter)
{

}

void lambda_p_serialization::parser::routine::operator () (boost::shared_ptr <lambda_p::core::expression> expression)
{

}

void lambda_p_serialization::parser::routine::add_name (std::wstring name, boost::shared_ptr <lambda_p::core::scatter> scatter_a, size_t position)
{
	auto existing (names.find (name));
	if (existing != names.end ())
	{
		names.insert (std::map <std::wstring, std::pair <boost::shared_ptr <lambda_p::core::scatter>, size_t>>::value_type (name, std::pair <boost::shared_ptr <lambda_p::core::scatter>, size_t> (scatter_a, position)));
	}
	else
	{
		std::wstringstream message;
		message << L"Identifier: ";
		message << name;
		message << L" has already been declared";
		parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (message.str ())));
	}
}