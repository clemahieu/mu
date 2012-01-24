#include <lambda_p_io/lexer/control.h>

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/lexer/multiline_comment.h>
#include <lambda_p_io/lexer/singleline_comment.h>
#include <lambda_p_io/lexer/error.h>
#include <lambda_p_io/tokens/parameters.h>
#include <lambda_p_io/lexer/hex_code.h>
#include <lambda_p_io/lexer/identifier.h>

lambda_p_io::lexer::control::control (lambda_p_io::lexer::lexer & lexer_a, lambda_p::position first_a)
	: lexer (lexer_a),
	first (first_a)
{
}

void lambda_p_io::lexer::control::lex (wchar_t character)
{
	if (character != L'\uffff')
	{
		switch (character)
		{
		case L'~':
			lexer.target (new lambda_p_io::tokens::parameters, lambda_p::context (first, lexer.position));
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
		case L'a':
			{
				lexer.state.pop ();
				auto identifier (boost::shared_ptr <lambda_p_io::lexer::identifier> (new lambda_p_io::lexer::identifier (lexer, first)));
				lexer.state.push (identifier);
				identifier->lex (L':');
				identifier->lex (L'a');
			}
			break;
		case L'u':
			{
				lexer.state.pop ();
				auto identifier (boost::shared_ptr <lambda_p_io::lexer::identifier> (new lambda_p_io::lexer::identifier (lexer, first)));
				lexer.state.push (identifier);
				identifier->lex (L':');
				identifier->lex (L'u');
			}
			break;
		default:
			std::wstring message (L"Unknown token: :");
			message.push_back (character);
			(*lexer.errors) (message, lambda_p::context (lexer.position, lexer.position));
			lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error));
			break;
		}
	}
	else
	{
		std::wstring message (L"End of stream when parsing control character");
		(*lexer.errors) (message, lambda_p::context (lexer.position, lexer.position));
		lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error));
	}
}