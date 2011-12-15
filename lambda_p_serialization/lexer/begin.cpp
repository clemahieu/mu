#include <lambda_p_serialization/lexer/begin.h>

#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p_serialization/lexer/lexer.h>
#include <lambda_p_serialization/lexer/complex_identifier.h>
#include <lambda_p_serialization/lexer/control.h>
#include <lambda_p_serialization/lexer/identifier.h>
#include <lambda_p_serialization/tokens/left_square.h>
#include <lambda_p_serialization/tokens/right_square.h>

lambda_p_serialization::lexer::begin::begin (lambda_p_serialization::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void lambda_p_serialization::lexer::begin::lex (wchar_t character)
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
		lexer.state.push (boost::shared_ptr <lambda_p_serialization::lexer::state> (new lambda_p_serialization::lexer::complex_identifier (lexer)));
		break;
	case L';':
		lexer.target (new lambda_p_serialization::tokens::divider);
		break;
	case L':':
		lexer.state.push (boost::shared_ptr <lambda_p_serialization::lexer::state> (new lambda_p_serialization::lexer::control (lexer)));
		break;
	case L'[':
		lexer.target (new lambda_p_serialization::tokens::left_square);
		break;
	case L']':
		lexer.target (new lambda_p_serialization::tokens::right_square);
		break;
	case L'\uffff':
		lexer.state.pop ();
		break;
	default:
		lexer.state.push (boost::shared_ptr <lambda_p_serialization::lexer::state> (new lambda_p_serialization::lexer::identifier (lexer)));
		lexer (character);
		break;
	}
}