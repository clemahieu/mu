#include <lambda_p_io/lexer/singleline_comment.h>

#include <lambda_p_io/lexer/lexer.h>

lambda_p_io::lexer::singleline_comment::singleline_comment (lambda_p_io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void lambda_p_io::lexer::singleline_comment::lex (wchar_t character)
{
	switch (character)
	{
	case L'\n':
	case L'\f':
		lexer.state.pop ();
		break;
	case L'\uffff':
		lexer.state.pop ();
		lexer (character);
		break;
	default:
		// Eat comment
		break;
	}
}