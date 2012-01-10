#include <lambda_p_io/lexer/control.h>

#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/lexer/multiline_comment.h>
#include <lambda_p_io/lexer/singleline_comment.h>
#include <lambda_p_io/lexer/error.h>
#include <lambda_p_io/tokens/parameters.h>

lambda_p_io::lexer::control::control (lambda_p_io::lexer::lexer & lexer_a)
	: complete (false),
	lexer (lexer_a)
{
}

void lambda_p_io::lexer::control::lex (wchar_t character)
{
	if (character != L'\uffff')
	{
		switch (character)
		{
		case L'~':
			lexer.target (new lambda_p_io::tokens::parameters);
			lexer.state.pop ();
			break;
		case L'[':
			lexer.state.pop ();
			lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::multiline_comment (lexer)));
			break;
		case L'-':
			lexer.state.pop ();
			lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::singleline_comment (lexer)));
			break;
		default:
			std::wstring message (L"Unknown token: :");
			message.push_back (character);
			lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error (message)));
			break;
		}
	}
	else
	{
		std::wstring message (L"End of stream when parsing control character");
		message.push_back (character);
		lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error (message)));
	}
}