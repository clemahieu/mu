#include <mu/io/lexer_lexer.h>

#include <mu/io/tokens_identifier.h>
#include <mu/io/tokens_divider.h>
#include <mu/io/lexer_state.h>
#include <mu/io/lexer_begin.h>
#include <mu/io/lexer_error.h>
#include <mu/io/lexer_control.h>
#include <mu/io/lexer_identifier.h>
#include <mu/io/lexer_multiline_comment.h>
#include <mu/io/lexer_singleline_comment.h>
#include <mu/io/lexer_complex_identifier.h>
#include <mu/io/lexer_error_target.h>
#include <mu/io/lexer_context.h>

#include <boost/circular_buffer.hpp>

#include <gc_cpp.h>

mu::io::lexer::lexer::lexer (mu::core::errors::error_target & errors_a, boost::function <void (mu::io::tokens::token const &)> target_a):
errors (errors_a),
target (target_a)
{
	reset ();
}

void mu::io::lexer::lexer::operator () (boost::circular_buffer <mu::io::lexer::context> & context_a)
{
	auto state_l (state.top ());
	state_l->lex (context_a);
}

void mu::io::lexer::lexer::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (new (GC) mu::io::lexer::begin (*this));
}