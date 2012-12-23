#include <mu/io/lexer_identifier.h>

#include <mu/io/lexer_lexer.h>
#include <mu/io/tokens_identifier.h>
#include <mu/io/lexer_hex_code.h>
#include <mu/io/lexer_control.h>
#include <mu/io/lexer_context.h>

#include <gc_cpp.h>

mu::io::lexer::identifier::identifier (mu::io::lexer::lexer & lexer_a, mu::io::position first_a):
first (first_a),
last (first_a),
lexer (lexer_a)
{
}

void mu::io::lexer::identifier::lex (boost::circular_buffer <mu::io::lexer::context> & context_a)
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
			case U';':
			case U'{':
            case U'}':
			case U'[':
			case U']':
			case U'\U0000ffff':
				{
					lexer.target (mu::io::tokens::identifier (mu::io::context (first, last), string));
					lexer.state.pop ();
					auto state (lexer.state.top ());
					state->lex (context_a);
				}
				break;
			case U':':
				switch (context_a [1].character)
				{
					case U'u':
						lexer.state.push (new (GC) mu::io::lexer::hex_code (8, *this));
						break;
					case U'a':
						lexer.state.push (new (GC) mu::io::lexer::hex_code (2, *this));
						break;
					default:
						lexer.target (mu::io::tokens::identifier (mu::io::context (first, last), string));
						lexer.state.pop ();
						auto state (new (GC) mu::io::lexer::control (lexer, context_a [0].position));
						lexer.state.push (state);
						state->lex (context_a);
						break;
				}
				break;
			default:
				add (context_a);
				break;
		}
	}
}

void mu::io::lexer::identifier::add (mu::io::lexer::context const & context_a)
{
	last = context_a.position;
	string.push_back (context_a.character);
}