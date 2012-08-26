#include <mu/io/lexer_begin.h>

#include <mu/io/tokens_implementor.h>
#include <mu/io/lexer_lexer.h>
#include <mu/io/lexer_complex_identifier.h>
#include <mu/io/lexer_control.h>
#include <mu/io/lexer_identifier.h>
#include <mu/io/lexer_state.h>
#include <mu/io/lexer_context.h>

#include <gc_cpp.h>

mu::io::lexer::begin::begin (mu::io::lexer::lexer & lexer_a):
lexer (lexer_a)
{
}

void mu::io::lexer::begin::lex (mu::io::lexer::context const & context_a)
{
	switch (context_a.character)
	{
	case U' ':
	case U'\t':
	case U'\n':
	case U'\f':
	case U'\0':
    case U'\r':
		// Eat whitespace
		break;
	case U'{':
		lexer.state.push (new (GC) mu::io::lexer::complex_identifier (lexer, context_a.position));
		break;
	case U';':
		lexer.target (new (GC) mu::io::tokens::divider (mu::io::context (context_a.position, context_a.position)));
		break;
	case U':':
		lexer.state.push (new (GC) mu::io::lexer::control (lexer, context_a.position));
		break;
	case U'[':
		lexer.target (new (GC) mu::io::tokens::left_square (mu::io::context (context_a.position, context_a.position)));
		break;
	case U']':
		lexer.target (new (GC) mu::io::tokens::right_square (mu::io::context (context_a.position, context_a.position)));
		break;
	case U'\U0000FFFF':
		{
			lexer.state.pop ();
			auto end (new (GC) mu::io::tokens::stream_end (mu::io::context (context_a.position, context_a.position)));
			lexer.target (end);
		}
		break;
	default:
		auto state (new (GC) mu::io::lexer::identifier (lexer, context_a.position));
		lexer.state.push (state);
		state->lex (context_a);
		break;
	}
}