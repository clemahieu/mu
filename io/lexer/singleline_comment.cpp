#include <io/lexer/singleline_comment.h>

#include <io/lexer/lexer.h>

mu::io::lexer::singleline_comment::singleline_comment (mu::io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void mu::io::lexer::singleline_comment::lex (wchar_t character)
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