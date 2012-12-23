#include <mu/io/lexer_singleline_comment.h>

#include <mu/io/lexer_lexer.h>
#include <mu/io/lexer_context.h>

mu::io::lexer::singleline_comment::singleline_comment (mu::io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void mu::io::lexer::singleline_comment::lex (boost::circular_buffer <mu::io::lexer::context> & context_a)
{
	switch (context_a [0].character)
	{
	case U'\n':
	case U'\f':
		lexer.state.pop ();
		break;
	case U'\U0000FFFF':
		lexer.state.pop ();
		lexer (context_a);
		break;
	default:
		// Eat comment
		break;
	}
}