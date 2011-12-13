#include <lambda_p/lexer/control.h>

#include <lambda_p/lexer/lexer.h>
#include <lambda_p/lexer/multiline_comment.h>
#include <lambda_p/lexer/singleline_comment.h>
#include <lambda_p/lexer/error.h>

lambda_p::lexer::control::control (lambda_p::lexer::lexer & lexer_a)
	: complete (false),
	lexer (lexer_a)
{
}

void lambda_p::lexer::control::lex (wchar_t character)
{
	if (character != '\uffff')
	{
		switch (character)
		{
		case L'*':
			lexer.state.pop ();
			lexer.state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::multiline_comment (lexer)));
			break;
		case L'/':
			lexer.state.pop ();
			lexer.state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::singleline_comment (lexer)));
			break;
		default:
			std::wstring message (L"Unknown token: :");
			message.push_back (character);
			lexer.state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::error (message)));
			break;
		}
	}
	else
	{
		std::wstring message (L"End of stream when parsing control character");
		message.push_back (character);
		lexer.state.push (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::error (message)));
	}
}