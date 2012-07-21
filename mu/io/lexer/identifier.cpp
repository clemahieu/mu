#include <mu/io/lexer/identifier.h>

#include <mu/io/lexer/lexer.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/lexer/hex_code.h>
#include <mu/io/lexer/control.h>

#include <gc_cpp.h>

mu::io::lexer::identifier::identifier (mu::io::lexer::lexer & lexer_a, mu::io::debugging::position first_a)
	: lookahead (false),
	first (first_a),
	last (first_a),
	lexer (lexer_a)
{
}

void mu::io::lexer::identifier::lex (mu::io::lexer::context const & context_a)
{				
	if (lookahead)
	{
		lookahead = false;
		switch (context_a.character)
		{
			case U'u':
				lexer.state.push (new (GC) mu::io::lexer::hex_code (8, *this));
				break;
			case U'a':
				lexer.state.push (new (GC) mu::io::lexer::hex_code (2, *this));
				break;
			default:
				mu::io::tokens::identifier * identifier = new (GC) mu::io::tokens::identifier (string);
				lexer.target (identifier, mu::io::debugging::context (first, last));
				lexer.state.pop ();
				auto state (new (GC) mu::io::lexer::control (lexer, lookahead_first));
				lexer.state.push (state);
				state->lex (context_a);
				break;
		}
	}
	else
	{
		switch (context_a.character)
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
					mu::io::tokens::identifier * identifier = new (GC) mu::io::tokens::identifier (string);
					lexer.target (identifier, mu::io::debugging::context (first, last));
					lexer.state.pop ();
					auto state (lexer.state.top ());
					state->lex (context_a);
				}
				break;
			case L':':
				lookahead_first = context_a.position;
				lookahead = true;
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