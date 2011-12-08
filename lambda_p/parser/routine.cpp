#include <lambda_p/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/token.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/core/node.h>
#include <lambda_p/parser/expression.h>
#include <lambda_p/core/list.h>

#include <boost/bind.hpp>

#include <sstream>

lambda_p::parser::routine::routine (lambda_p::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a)
	: target (target_a),
	parser (parser_a),
	state (lambda_p::parser::routine_state::surface),
	routine_m (new lambda_p::core::routine)
{
}

void lambda_p::parser::routine::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (state)
	{
	case lambda_p::parser::routine_state::surface:
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
				auto identifier (static_cast <lambda_p::tokens::identifier *> (token));
				auto existing (names.find (identifier->string));
				if (existing == names.end ())
				{
					auto expression (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
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
		case lambda_p::tokens::token_id_divider:
			state = lambda_p::parser::routine_state::expression_begin;
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
	}
}