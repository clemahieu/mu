#include <lambda_p_io/lexer/multiline_comment.h>

#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/lexer/error.h>
#include <core/errors/error_target.h>

lambda_p_io::lexer::multiline_comment::multiline_comment (lambda_p_io::lexer::lexer & lexer_a)
	: have_colon (false),
	lexer (lexer_a)
{
}

void lambda_p_io::lexer::multiline_comment::lex (wchar_t character)
{	
	if (character != L'\uffff')
	{
		if (have_colon)
		{
			switch (character)
			{
			case L']':
				lexer.state.pop ();
				break;
			case L'[':
				have_colon = false;
				lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::multiline_comment (lexer)));
				break;
			case L':':
				// Remain in have_colon state
				break;
			default:
				have_colon = false;
				break;
			}
		}
		else
		{
			switch (character)
			{
			case L':':
				have_colon = true;
				break;
			}
		}
	}
	else
	{
		(*lexer.errors) (L"End of stream inside multiline comment", mu::core::context (lexer.position, lexer.position));
		lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error));
	}
}