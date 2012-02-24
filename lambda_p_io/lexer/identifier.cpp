#include <lambda_p_io/lexer/identifier.h>

#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/lexer/hex_code.h>
#include <lambda_p_io/lexer/control.h>

#include <boost/make_shared.hpp>

lambda_p_io::lexer::identifier::identifier (lambda_p_io::lexer::lexer & lexer_a, mu::core::position first_a)
	: lexer (lexer_a),
	lookahead (false),
	first (first_a),
	last (first_a)
{
}

void lambda_p_io::lexer::identifier::lex (wchar_t character)
{				
	if (lookahead)
	{
		lookahead = false;
		switch (character)
		{
			case L'u':
				lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::hex_code (8, *this)));
				break;
			case L'a':
				lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::hex_code (2, *this)));
				break;
			default:
				lambda_p_io::tokens::identifier * identifier = new lambda_p_io::tokens::identifier (string);
				lexer.target (identifier, mu::core::context (first, last));
				lexer.state.pop ();
				auto state (boost::make_shared <lambda_p_io::lexer::control> (lexer, lookahead_first));
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
			case L';':
			case L'|':
			case L'[':
			case L']':
			case L'\uffff':
				{
					lambda_p_io::tokens::identifier * identifier = new lambda_p_io::tokens::identifier (string);
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

void lambda_p_io::lexer::identifier::add (wchar_t character)
{
	last = lexer.position;
	string.push_back (character);
}