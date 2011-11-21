#include <lambda_p/lexer/singleline_comment.h>

#include <lambda_p/lexer/lexer.h>

lambda_p::lexer::singleline_comment::singleline_comment (lambda_p::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

lambda_p::lexer::state_id lambda_p::lexer::singleline_comment::state_type ()
{
	return lambda_p::lexer::state_singleline_comment;
}

void lambda_p::lexer::singleline_comment::lex (wchar_t character)
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