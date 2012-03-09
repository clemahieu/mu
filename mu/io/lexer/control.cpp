#include <mu/io/lexer/control.h>

#include <mu/core/errors/error_target.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/lexer/multiline_comment.h>
#include <mu/io/lexer/singleline_comment.h>
#include <mu/io/lexer/error.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/lexer/hex_code.h>
#include <mu/io/lexer/identifier.h>

mu::io::lexer::control::control (mu::io::lexer::lexer & lexer_a, mu::core::position first_a)
	: first (first_a),
	lexer (lexer_a)
{
}

void mu::io::lexer::control::lex (wchar_t character)
{
	if (character != L'\uffff')
	{
		switch (character)
		{
		case L'~':
			lexer.target (new mu::io::tokens::parameters, mu::core::context (first, lexer.position));
			lexer.state.pop ();
			break;
		case L'{':
			lexer.state.pop ();
			lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::multiline_comment (lexer)));
			break;
		case L'-':
			lexer.state.pop ();
			lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::singleline_comment (lexer)));
			break;
		case L'a':
			{
				lexer.state.pop ();
				auto identifier (boost::shared_ptr <mu::io::lexer::identifier> (new mu::io::lexer::identifier (lexer, first)));
				lexer.state.push (identifier);
				identifier->lex (L':');
				identifier->lex (L'a');
			}
			break;
		case L'u':
			{
				lexer.state.pop ();
				auto identifier (boost::shared_ptr <mu::io::lexer::identifier> (new mu::io::lexer::identifier (lexer, first)));
				lexer.state.push (identifier);
				identifier->lex (L':');
				identifier->lex (L'u');
			}
			break;
		default:
			std::wstring message (L"Unknown token: :");
			message.push_back (character);
			(*lexer.errors) (message, mu::core::context (lexer.position, lexer.position));
			lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::error));
			break;
		}
	}
	else
	{
		std::wstring message (L"End of stream when parsing control character");
		(*lexer.errors) (message, mu::core::context (lexer.position, lexer.position));
		lexer.state.push (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::error));
	}
}