#include <lambda_p_serialization/parser/parser.h>

#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p_serialization/parser/begin.h>
#include <lambda_p_serialization/parser/error.h>
#include <lambda_p_serialization/parser/finished.h>

#include <boost/bind.hpp>

#include <map>

lambda_p_serialization::parser::parser::parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> & keywords_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> & globals_a)
	: target (target_a),
	keywords (keywords_a),
	globals (globals_a)
{
	reset ();
}

void lambda_p_serialization::parser::parser::operator () (lambda_p_serialization::tokens::token * token)
{
	auto identifier (dynamic_cast <lambda_p_serialization::tokens::identifier *> (token));
	if (identifier != nullptr)
	{
		auto keyword (keywords.find (identifier->string));
		if (keyword != keywords.end ())
		{
			auto new_state (keyword->second->create (*this, state.top ()));
			new_state->parse (identifier);
		}
		else
		{
			process_token (token);
		}
	}
	else
	{
		process_token (token);
	}
}

void lambda_p_serialization::parser::parser::process_token (lambda_p_serialization::tokens::token * token)
{
	auto state_l (state.top ());
	(*token) (*state_l);
}

void lambda_p_serialization::parser::parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
    state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::finished (*this)));
	state.push (boost::shared_ptr <lambda_p_serialization::parser::state> (new lambda_p_serialization::parser::begin (*this, target)));
}

boost::shared_ptr <lambda_p_serialization::parser::error> lambda_p_serialization::parser::parser::error ()
{
	boost::shared_ptr <lambda_p_serialization::parser::error> result;
	if (!state.empty ())
	{
		result = boost::dynamic_pointer_cast <lambda_p_serialization::parser::error> (state.top ());
	}
	return result;
}