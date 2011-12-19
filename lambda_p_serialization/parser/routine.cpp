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
#include <lambda_p_serialization/parser/signature.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/core/tee.h>
#include <lambda_p/core/scatter.h>
#include <lambda_p/core/entry.h>

#include <boost/bind.hpp>

#include <sstream>

lambda_p_serialization::parser::routine::routine (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a)
	: target (target_a),
	parser (parser_a),
	state (lambda_p_serialization::parser::routine_state::surface_begin),
	routine_m (new lambda_p::core::routine),
	names (parser.globals),
	parameter_scatter (new lambda_p::core::scatter),
	parameter_tee (new lambda_p::core::tee)
{
	routine_m->input = boost::shared_ptr <lambda_p::core::entry> (new lambda_p::core::entry (parameter_tee));
	parameter_tee->targets.push_back (parameter_scatter);
}

void lambda_p_serialization::parser::routine::parse (lambda_p_serialization::tokens::token * token)
{
	auto token_id (token->token_id ());
	switch (state)
	{
	case lambda_p_serialization::parser::routine_state::surface_begin:
		switch (token_id)
		{
		case lambda_p_serialization::tokens::token_id_left_square:
			state = lambda_p_serialization::parser::routine_state::surface_end;
			parser.state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::signature (parser, *this)));
			break;
		default:
			std::wstringstream message;
			message << L"Expecting an routine signature, have: ";
			message << token->token_name ();
			boost::shared_ptr <lambda_p_serialization::parser::state> new_state (new lambda_p_serialization::parser::error (message.str ()));
			parser.state.push (new_state);
			break;
		}
		break;
	case lambda_p_serialization::parser::routine_state::surface_end:
		switch (token_id)
		{
		case lambda_p_serialization::tokens::token_id_right_square:
			state = lambda_p_serialization::parser::routine_state::expression_begin;
			break;
		default:
			assert (false);
			break;
		}
		break;
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

void lambda_p_serialization::parser::routine::operator () (std::vector <std::wstring> parameters, std::wstring full_parameter)
{
	size_t position (0);
	for (auto i (parameters.begin ()), j (parameters.end ()); i != j; ++i, ++position)
	{
		add_name (*i, boost::shared_ptr <lambda_p_serialization::parser::reference> (new lambda_p_serialization::parser::reference_scatter (parameter_scatter, position)));
	}
	if (!full_parameter.empty ())
	{
		add_name (full_parameter, boost::shared_ptr <lambda_p_serialization::parser::reference> (new lambda_p_serialization::parser::reference_tee (parameter_tee)));
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