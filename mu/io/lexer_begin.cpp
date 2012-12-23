#include <mu/io/lexer_begin.h>

#include <mu/io/tokens_implementor.h>
#include <mu/io/lexer_lexer.h>
#include <mu/io/lexer_complex_identifier.h>
#include <mu/io/lexer_control.h>
#include <mu/io/lexer_identifier.h>
#include <mu/io/lexer_state.h>
#include <mu/io/lexer_context.h>
#include <mu/io/lexer_hex_code.h>

#include <gc_cpp.h>

mu::io::lexer::begin::begin (mu::io::lexer::lexer & lexer_a):
lexer (lexer_a)
{
}

void mu::io::lexer::begin::lex (boost::circular_buffer <mu::io::lexer::context> & context_a)
{
	assert (context_a.size () >= 2);
	switch (context_a [0].character)
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
		lexer.state.push (new (GC) mu::io::lexer::complex_identifier (lexer, context_a [0].position));
		break;
	case U';':
        lexer.target (mu::io::tokens::divider (mu::io::context (context_a [0].position, context_a [0].position)));
		break;
	case U':':
		switch (context_a [1].character)
		{
			case U'a':
			{
				auto identifier (new (GC) mu::io::lexer::identifier (lexer, context_a [0].position));
				lexer.state.push (identifier);
				lexer.state.push (new (GC) mu::io::lexer::hex_code (2, *identifier));
			}
				break;
			case U'u':
			{
				auto identifier (new (GC) mu::io::lexer::identifier (lexer, context_a [0].position));
				lexer.state.push (identifier);
				lexer.state.push (new (GC) mu::io::lexer::hex_code (8, *identifier));
			}
				break;
			default:
				lexer.state.push (new (GC) mu::io::lexer::control (lexer, context_a [0].position));
				break;
		}
		break;
	case U'[':
        lexer.target (mu::io::tokens::left_square (mu::io::context (context_a [0].position, context_a [0].position)));
		break;
	case U']':
        lexer.target (mu::io::tokens::right_square (mu::io::context (context_a [0].position, context_a [0].position)));
		break;
	case U'\U0000FFFF':
        lexer.state.pop ();
        lexer.target (mu::io::tokens::stream_end (mu::io::context (context_a [0].position, context_a [0].position)));
		break;
	default:
		auto state (new (GC) mu::io::lexer::identifier (lexer, context_a [0].position));
		lexer.state.push (state);
		state->lex (context_a);
		break;
	}
}