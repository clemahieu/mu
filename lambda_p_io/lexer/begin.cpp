#include <lambda_p_io/lexer/begin.h>

#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/lexer/complex_identifier.h>
#include <lambda_p_io/lexer/control.h>
#include <lambda_p_io/lexer/identifier.h>
#include <lambda_p_io/tokens/left_square.h>
#include <lambda_p_io/tokens/right_square.h>
#include <lambda_p_io/tokens/stream_end.h>
#include <lambda_p_io/lexer/state.h>

lambda_p_io::lexer::begin::begin (lambda_p_io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void lambda_p_io::lexer::begin::lex (wchar_t character)
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
		lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::complex_identifier (lexer)));
		break;
	case L';':
		lexer.target (new lambda_p_io::tokens::divider, mu::core::context (lexer.position, lexer.position));
		break;
	case L':':
		lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::control (lexer, lexer.position)));
		break;
	case L'[':
		lexer.target (new lambda_p_io::tokens::left_square, mu::core::context (lexer.position, lexer.position));
		break;
	case L']':
		lexer.target (new lambda_p_io::tokens::right_square, mu::core::context (lexer.position, lexer.position));
		break;
	case L'\uffff':
		lexer.state.pop ();
		lexer.target (new lambda_p_io::tokens::stream_end, mu::core::context (lexer.position, lexer.position));
		break;
	default:
		auto state (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::identifier (lexer, lexer.position)));
		lexer.state.push (state);
		state->lex (character);
		break;
	}
}