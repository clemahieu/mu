#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/divider.h>

#include <lambda_p_io/lexer/state.h>
#include <lambda_p_io/lexer/begin.h>
#include <lambda_p_io/lexer/error.h>
#include <lambda_p_io/lexer/control.h>
#include <lambda_p_io/lexer/identifier.h>
#include <lambda_p_io/lexer/multiline_comment.h>
#include <lambda_p_io/lexer/singleline_comment.h>
#include <lambda_p_io/lexer/complex_identifier.h>

#include <boost/circular_buffer.hpp>

lambda_p_io::lexer::lexer::lexer (boost::function < void (lambda_p_io::tokens::token *)> target_a)
	: target (target_a)
{
	state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::begin (*this)));
}

lambda_p_io::lexer::lexer::~lexer ()
{
}

void lambda_p_io::lexer::lexer::operator () (wchar_t character)
{
	auto state_l (state.top ());
	state_l->lex (character);
}

void lambda_p_io::lexer::lexer::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::begin (*this)));
}

boost::shared_ptr <lambda_p_io::lexer::error> lambda_p_io::lexer::lexer::error ()
{
	boost::shared_ptr <lambda_p_io::lexer::error> result;
	if (!state.empty ())
	{
		result = boost::dynamic_pointer_cast <lambda_p_io::lexer::error> (state.top ());
	}
	return result;
}