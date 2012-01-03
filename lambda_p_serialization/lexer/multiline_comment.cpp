#include <lambda_p_serialization/lexer/multiline_comment.h>

#include <lambda_p_serialization/lexer/lexer.h>
#include <lambda_p_serialization/lexer/error.h>

lambda_p_serialization::lexer::multiline_comment::multiline_comment (lambda_p_serialization::lexer::lexer & lexer_a)
	: have_colon (false),
	lexer (lexer_a)
{
}

void lambda_p_serialization::lexer::multiline_comment::lex (wchar_t character)
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
				lexer.state.push (boost::shared_ptr <lambda_p_serialization::lexer::state> (new lambda_p_serialization::lexer::multiline_comment (lexer)));
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
		std::wstring message (L"End of stream inside multiline comment");
		lexer.state.push (boost::shared_ptr <lambda_p_serialization::lexer::state> (new lambda_p_serialization::lexer::error (message)));
	}
}