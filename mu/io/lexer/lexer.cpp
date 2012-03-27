#include <mu/io/lexer/lexer.h>

#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/lexer/state.h>
#include <mu/io/lexer/begin.h>
#include <mu/io/lexer/error.h>
#include <mu/io/lexer/control.h>
#include <mu/io/lexer/identifier.h>
#include <mu/io/lexer/multiline_comment.h>
#include <mu/io/lexer/singleline_comment.h>
#include <mu/io/lexer/complex_identifier.h>
#include <mu/io/lexer/error_target.h>

#include <boost/circular_buffer.hpp>
#include <boost/make_shared.hpp>

mu::io::lexer::lexer::lexer (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::function <void (mu::io::tokens::token *, mu::io::debugging::context)> target_a, boost::shared_ptr <mu::io::debugging::stream> stream_a)
	: errors (boost::make_shared <mu::io::lexer::error_target> (*this, errors_a)),
	target (target_a),
	stream (stream_a)
{
	reset ();
}

void mu::io::lexer::lexer::operator () (wchar_t character)
{
	uint32_t character_l (0);
	character_l = character;
	hash.Update ((byte *)&character_l, 4);
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

void mu::io::lexer::lexer::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::begin (*this)));
	hash.Restart ();
}