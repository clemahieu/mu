#include <lambda_p_serialization/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p_serialization/tokens/token.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p/core/expression.h>
#include <lambda_p_serialization/parser/expression.h>
#include <lambda_p_serialization/parser/reference_scatter.h>
#include <lambda_p_serialization/parser/reference_tee.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/core/tee.h>
#include <lambda_p/core/scatter.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/core/collapse.h>
#include <lambda_p/core/adapter.h>
#include <lambda_p/core/identity.h>
#include <lambda_p_serialization/parser/reference_fixed.h>

#include <boost/bind.hpp>

#include <sstream>

lambda_p_serialization::parser::routine::routine (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a)
	: target (target_a),
	parser (parser_a),
	state (lambda_p_serialization::parser::routine_state::expression_begin),
	tee (new lambda_p::core::tee),
	routine_m (new lambda_p::core::routine),
	names (parser.globals)
{
	auto collapse (boost::shared_ptr <lambda_p::core::collapse> (new lambda_p::core::collapse (tee, routine_m->errors)));
	routine_m->input->next = collapse;
	names [std::wstring (L"~")] = boost::shared_ptr <lambda_p_serialization::parser::reference_tee> (new lambda_p_serialization::parser::reference_tee (tee));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> identity_expressions;
	identity_expressions.push_back (boost::shared_ptr <lambda_p::core::identity> (new lambda_p::core::identity));
	names [std::wstring (L".identity")] = boost::shared_ptr <lambda_p_serialization::parser::reference_fixed> (new lambda_p_serialization::parser::reference_fixed (routine_m->input, identity_expressions));
}

void lambda_p_serialization::parser::routine::parse (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (state)
	{
	case lambda_p_serialization::parser::routine_state::expression_begin:
		switch (token_id)
		{
		case lambda_p_serialization::tokens::token_id_left_square:
			state = lambda_p_serialization::parser::routine_state::expression_end;
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::expression (parser, *this, routine_m->output)));
			break;
		default:
			std::wstringstream message;
			message << L"Expecting an expression as routine body, have: ";
			message << token->token_name ();
			boost::shared_ptr <lambda_p_serialization::parser::state> new_state (new lambda_p_serialization::parser::error (message.str ()));
			parser.state.push (new_state);
			break;
		}
		break;
	case lambda_p_serialization::parser::routine_state::expression_end:
		switch (token_id)
		{
		case lambda_p_serialization::tokens::token_id_right_square:
			target (routine_m);
			parser.state.pop ();
			break;
		default:
			assert (false);
			break;
		}
		break;
	case lambda_p_serialization::parser::routine_state::state_end:
		parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::error (L"Token received in end state")));
		break;
	}
}

void lambda_p_serialization::parser::routine::add_name (std::wstring name, boost::shared_ptr <lambda_p_serialization::parser::reference> reference)
{
	auto existing (names.find (name));
	if (existing == names.end ())
	{
		names.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>>::value_type (name, reference));
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