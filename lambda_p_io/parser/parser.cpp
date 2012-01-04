#include <lambda_p_io/parser/parser.h>

#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/divider.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/parser/begin.h>
#include <lambda_p_io/parser/error.h>
#include <lambda_p_io/parser/finished.h>

#include <boost/bind.hpp>

#include <map>

lambda_p_io::parser::parser::parser (boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a)
	: target (target_a)
{
	reset ();
}

void lambda_p_io::parser::parser::operator () (lambda_p_io::tokens::token * token)
{
	auto state_l (state.top ());
	(*token) (state_l.get ());
}

void lambda_p_io::parser::parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::finished (*this)));
	state.push (boost::shared_ptr <lambda_p_io::tokens::visitor> (new lambda_p_io::parser::begin (*this, target)));
}

boost::shared_ptr <lambda_p_io::parser::error> lambda_p_io::parser::parser::error ()
{
	boost::shared_ptr <lambda_p_io::parser::error> result;
	if (!state.empty ())
	{
		result = boost::dynamic_pointer_cast <lambda_p_io::parser::error> (state.top ());
	}
	return result;
}