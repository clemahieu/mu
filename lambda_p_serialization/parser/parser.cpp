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

lambda_p_serialization::parser::parser::parser (boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target_a)
	: target (target_a)
{
	reset ();
}

void lambda_p_serialization::parser::parser::operator () (lambda_p_serialization::tokens::token * token)
{
	auto state_l (state.top ());
	(*token) (state_l.get ());
}

void lambda_p_serialization::parser::parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::finished (*this)));
	state.push (boost::shared_ptr <lambda_p_serialization::tokens::visitor> (new lambda_p_serialization::parser::begin (*this, target)));
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