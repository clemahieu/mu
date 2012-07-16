#include <mu/io/lexer/singleline_comment.h>

#include <mu/io/lexer/lexer.h>

mu::io::lexer::singleline_comment::singleline_comment (mu::io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void mu::io::lexer::singleline_comment::lex (char32_t character)
{
	switch (character)
	{
	case U'\n':
	case U'\f':
		lexer.state.pop ();
		break;
	case U'\U0000FFFF':
		lexer.state.pop ();
		lexer (character);
		break;
	default:
		// Eat comment
		break;
	}
}