#include <lambda_p_io/lexer/identifier.h>

#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/tokens/identifier.h>

lambda_p_io::lexer::identifier::identifier (lambda_p_io::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

void lambda_p_io::lexer::identifier::lex (wchar_t character)
{				
	switch (character)
	{
	case L' ':
	case L'\t':
	case L'\n':
	case L'\f':
	case L'\0':
	case L':':
	case L';':
	case L'|':
	case L'[':
	case L']':
	case L'\uffff':
		{
			lambda_p_io::tokens::identifier * identifier = new lambda_p_io::tokens::identifier (string);
			lexer.target (identifier);
			lexer.state.pop ();
			lexer (character);
		}
		break;
	default:
		string.push_back (character);
		break;
	}
}