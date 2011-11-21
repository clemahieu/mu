#include <lambda_p/lexer/identifier.h>

#include <lambda_p/lexer/lexer.h>
#include <lambda_p/tokens/identifier.h>

lambda_p::lexer::identifier::identifier (lambda_p::lexer::lexer & lexer_a)
	: lexer (lexer_a)
{
}

lambda_p::lexer::state_id lambda_p::lexer::identifier::state_type ()
{
	return lambda_p::lexer::state_identifier;
}

void lambda_p::lexer::identifier::lex (wchar_t character)
{				
	switch (character)
	{
	case L' ':
	case L'\t':
	case L'\n':
	case L'\f':
	case L';':
	case L'`':
	case L'|':
	case L':':
	case L'\0':
	case L'\uffff':
		{
			lambda_p::tokens::identifier * identifier = new lambda_p::tokens::identifier (string);
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