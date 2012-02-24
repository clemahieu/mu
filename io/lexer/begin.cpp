#include <io/lexer/begin.h>

#include <io/tokens/divider.h>
#include <io/lexer/lexer.h>
#include <io/lexer/complex_identifier.h>
#include <io/lexer/control.h>
#include <io/lexer/identifier.h>
#include <io/tokens/left_square.h>
#include <io/tokens/right_square.h>
#include <io/tokens/stream_end.h>
#include <io/lexer/state.h>

mu::io::lexer::begin::begin (mu::io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void mu::io::lexer::begin::lex (wchar_t character)
{
	switch (character)
	{
	case L' ':
	case L'\t':
	case L'\n':
	case L'\f':
	case L'\0':
		// Eat whitespace
		break;
	case L'|':
		lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::complex_identifier (lexer)));
		break;
	case L';':
		lexer.target (new mu::io::tokens::divider, mu::core::context (lexer.position, lexer.position));
		break;
	case L':':
		lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::control (lexer, lexer.position)));
		break;
	case L'[':
		lexer.target (new mu::io::tokens::left_square, mu::core::context (lexer.position, lexer.position));
		break;
	case L']':
		lexer.target (new mu::io::tokens::right_square, mu::core::context (lexer.position, lexer.position));
		break;
	case L'\uffff':
		lexer.state.pop ();
		lexer.target (new mu::io::tokens::stream_end, mu::core::context (lexer.position, lexer.position));
		break;
	default:
		auto state (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::identifier (lexer, lexer.position)));
		lexer.state.push (state);
		state->lex (character);
		break;
	}
}