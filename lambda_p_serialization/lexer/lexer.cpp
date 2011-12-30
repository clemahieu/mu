#include <lambda_p_serialization/lexer/lexer.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/tokens/divider.h>

#include <lambda_p_serialization/lexer/state.h>
#include <lambda_p_serialization/lexer/begin.h>
#include <lambda_p_serialization/lexer/error.h>
#include <lambda_p_serialization/lexer/control.h>
#include <lambda_p_serialization/lexer/identifier.h>
#include <lambda_p_serialization/lexer/multiline_comment.h>
#include <lambda_p_serialization/lexer/singleline_comment.h>
#include <lambda_p_serialization/lexer/complex_identifier.h>

#include <boost/circular_buffer.hpp>

lambda_p_serialization::lexer::lexer::lexer (boost::function < void (lambda_p_serialization::tokens::token *)> target_a)
	: target (target_a)
{
	state.push (boost::shared_ptr <lambda_p_serialization::lexer::state> (new lambda_p_serialization::lexer::begin (*this)));
}

lambda_p_serialization::lexer::lexer::~lexer ()
{
}

void lambda_p_serialization::lexer::lexer::operator () (wchar_t character)
{
	auto state_l (state.top ());
	state_l->lex (character);
}

void lambda_p_serialization::lexer::lexer::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <lambda_p_serialization::lexer::state> (new lambda_p_serialization::lexer::begin (*this)));
}

boost::shared_ptr <lambda_p_serialization::lexer::error> lambda_p_serialization::lexer::lexer::error ()
{
	boost::shared_ptr <lambda_p_serialization::lexer::error> result;
	if (!state.empty ())
	{
		result = boost::dynamic_pointer_cast <lambda_p_serialization::lexer::error> (state.top ());
	}
	return result;
}