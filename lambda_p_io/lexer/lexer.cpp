#include <lambda_p_io/lexer/lexer.h>
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

lambda_p_io::lexer::lexer::lexer (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::function < void (lambda_p_io::tokens::token *, lambda_p::context)> target_a)
	: target (target_a),
	errors (errors_a)
{
	state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::begin (*this)));
}

void lambda_p_io::lexer::lexer::operator () (wchar_t character)
{
	auto state_l (state.top ());
	state_l->lex (character);
	++position.character;
	if (character == L'\n')
	{
		++position.row;
		position.column = 1;
	}
	else
	{
		++position.column;
	}
}

void lambda_p_io::lexer::lexer::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::begin (*this)));
}