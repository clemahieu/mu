#include <lambda_p/lexer/begin.h>

#include <lambda_p/tokens/data.h>
#include <lambda_p/tokens/divider.h>
#include <lambda_p/lexer/lexer.h>
#include <lambda_p/lexer/complex_identifier.h>
#include <lambda_p/lexer/control.h>
#include <lambda_p/lexer/identifier.h>

lambda_p::lexer::begin::begin (lambda_p::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void lambda_p::lexer::begin::lex (wchar_t character)
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
	case L'`':
		{
			lambda_p::tokens::data * token = new lambda_p::tokens::data;
			lexer.target (token);
		}
		break;
	case L'|':
		lexer.state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::complex_identifier (lexer)));
		break;
	case L';':
		{
			lambda_p::tokens::divider * token = new lambda_p::tokens::divider;
			lexer.target (token);
		}
		break;
	case L':':
		lexer.state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::control (lexer)));
		break;
	case L'\uffff':
		lexer.state.pop ();
		break;
	default:
		lexer.state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::identifier (lexer)));
		lexer (character);
		break;
	}
}