#include <mu/io/lexer/multiline_comment.h>

#include <mu/io/lexer/lexer.h>
#include <mu/io/lexer/error.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/lexer/context.h>

#include <gc_cpp.h>

mu::io::lexer::multiline_comment::multiline_comment (mu::io::lexer::lexer & lexer_a)
	: have_colon (false),
	lexer (lexer_a)
{
}

void mu::io::lexer::multiline_comment::lex (mu::io::lexer::context const & context_a)
{	
	if (context_a.character != U'\U0000ffff')
	{
		if (have_colon)
		{
			switch (context_a.character)
			{
			case U')':
				lexer.state.pop ();
				break;
			case U'(':
				have_colon = false;
				lexer.state.push (new (GC) mu::io::lexer::multiline_comment (lexer));
				break;
			case U':':
				// Remain in have_colon state
				break;
			default:
				have_colon = false;
				break;
			}
		}
		else
		{
			switch (context_a.character)
			{
			case U':':
				have_colon = true;
				break;
			}
		}
	}
	else
	{
		(*lexer.errors) (U"End of stream inside multiline comment");
		lexer.state.push (new (GC) mu::io::lexer::error);
	}
}