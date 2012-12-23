#include <mu/io/lexer_multiline_comment.h>

#include <mu/io/lexer_lexer.h>
#include <mu/io/lexer_error.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/lexer_context.h>

#include <gc_cpp.h>

mu::io::lexer::multiline_comment::multiline_comment (mu::io::lexer::lexer & lexer_a):
lexer (lexer_a)
{
}

void mu::io::lexer::multiline_comment::lex (boost::circular_buffer <mu::io::lexer::context> & context_a)
{	
	assert (context_a.size () >= 2);
	switch (context_a [0].character)
	{
		case U':':
			switch (context_a[1].character)
			{
				case U')':
					lexer.state.pop ();
					break;
				case U'(':
					lexer.state.push (new (GC) mu::io::lexer::multiline_comment (lexer));
					break;
				default:
					break;
			}
		case U'\U0000ffff':
		{
			lexer.errors (U"End of stream inside multiline comment");
			lexer.state.push (new (GC) mu::io::lexer::error);
		}
		break;
	}
}