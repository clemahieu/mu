#include <lambda_p/lexer/lexer.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/divider.h>
#include <lambda_p/tokens/complex_identifier.h>

#include <lambda_p/lexer/state.h>
#include <lambda_p/lexer/begin.h>
#include <lambda_p/lexer/error.h>
#include <lambda_p/lexer/control.h>
#include <lambda_p/lexer/identifier.h>
#include <lambda_p/lexer/multiline_comment.h>
#include <lambda_p/lexer/singleline_comment.h>
#include <lambda_p/lexer/complex_identifier.h>

#include <boost/circular_buffer.hpp>

lambda_p::lexer::lexer::lexer (boost::function < void (lambda_p::tokens::token *)> target_a)
	: target (target_a)
{
	state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::begin (*this)));
}

lambda_p::lexer::lexer::~lexer ()
{
}

void lambda_p::lexer::lexer::operator () (wchar_t character)
{
	auto state_l (state.top ());
	state_l->lex (character);
}

void lambda_p::lexer::lexer::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::begin (*this)));
}

boost::shared_ptr <lambda_p::lexer::error> lambda_p::lexer::lexer::error ()
{
	boost::shared_ptr <lambda_p::lexer::error> result;
	if (!state.empty ())
	{
		result = boost::dynamic_pointer_cast <lambda_p::lexer::error> (state.top ());
	}
	return result;
}