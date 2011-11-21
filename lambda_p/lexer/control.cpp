#include <lambda_p/lexer/control.h>

#include <lambda_p/lexer/lexer.h>
#include <lambda_p/lexer/multiline_comment.h>
#include <lambda_p/lexer/singleline_comment.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/lexer/error.h>

lambda_p::lexer::control::control (lambda_p::lexer::lexer & lexer_a)
	: complete (false),
	lexer (lexer_a)
{
}

lambda_p::lexer::state_id lambda_p::lexer::control::state_type ()
{
	return lambda_p::lexer::state_control;
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
		case L';':
			{
				lambda_p::tokens::routine_end * token = new lambda_p::tokens::routine_end;
				lexer.target (token);
				lexer.state.pop ();
			}
			break;
		default:
			std::wstring message (L"Unknown token: #");
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