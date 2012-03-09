#include <mu/io/lexer/identifier.h>

#include <mu/io/lexer/lexer.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/lexer/hex_code.h>
#include <mu/io/lexer/control.h>

#include <boost/make_shared.hpp>

mu::io::lexer::identifier::identifier (mu::io::lexer::lexer & lexer_a, mu::core::position first_a)
	: lookahead (false),
	first (first_a),
	last (first_a),
	lexer (lexer_a)
{
}

void mu::io::lexer::identifier::lex (wchar_t character)
{				
	if (lookahead)
	{
		lookahead = false;
		switch (character)
		{
			case L'u':
				lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::hex_code (8, *this)));
				break;
			case L'a':
				lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::hex_code (2, *this)));
				break;
			default:
				mu::io::tokens::identifier * identifier = new mu::io::tokens::identifier (string);
				lexer.target (identifier, mu::core::context (first, last));
				lexer.state.pop ();
				auto state (boost::make_shared <mu::io::lexer::control> (lexer, lookahead_first));
				lexer.state.push (state);
				state->lex (character);
				break;
		}
	}
	else
	{
		switch (character)
		{
			case L' ':
			case L'\t':
			case L'\n':
			case L'\f':
			case L'\0':
            case L'\r':
			case L';':
			case L'|':
			case L'[':
			case L']':
			case L'\uffff':
				{
					mu::io::tokens::identifier * identifier = new mu::io::tokens::identifier (string);
					lexer.target (identifier, mu::core::context (first, last));
					lexer.state.pop ();
					auto state (lexer.state.top ());
					state->lex (character);
				}
				break;
			case L':':
				lookahead_first = lexer.position;
				lookahead = true;
				break;
			default:
				add (character);
				break;
		}
	}
}

void mu::io::lexer::identifier::add (wchar_t character)
{
	last = lexer.position;
	string.push_back (character);
}