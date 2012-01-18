#include <lambda_p_io/lexer/control.h>

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/lexer/multiline_comment.h>
#include <lambda_p_io/lexer/singleline_comment.h>
#include <lambda_p_io/lexer/error.h>
#include <lambda_p_io/tokens/parameters.h>
#include <lambda_p_io/lexer/utf_character.h>

lambda_p_io::lexer::control::control (lambda_p_io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
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
		case L'0':
		case L'1':
		case L'2':
		case L'3':
		case L'4':
		case L'5':
		case L'6':
		case L'7':
		case L'8':
		case L'9':
		case L'a':
		case L'A':
		case L'b':
		case L'B':
		case L'c':
		case L'C':
		case L'd':
		case L'D':
		case L'e':
		case L'E':
		case L'f':
		case L'F':
			lexer.state.pop ();
			lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::utf_character (lexer)));
			break;
		default:
			std::wstring message (L"Unknown token: :");
			message.push_back (character);
			(*lexer.errors) (message);
			lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error));
			break;
		}
	}
	else
	{
		std::wstring message (L"End of stream when parsing control character");
		(*lexer.errors) (message);
		lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error));
	}
}