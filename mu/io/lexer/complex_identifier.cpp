#include <mu/io/lexer/complex_identifier.h>

#include <mu/io/tokens/identifier.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/lexer/error.h>
#include <mu/core/errors/error_target.h>

mu::io::lexer::complex_identifier::complex_identifier (mu::io::lexer::lexer & lexer_a)
	: have_end_token (false),
	first (lexer_a.position),
	last (lexer_a.position),
	lexer (lexer_a)
{
}

bool mu::io::lexer::complex_identifier::match ()
{
	bool result (last_characters.size () == end_token.size ());
	if (result)
	{
		boost::circular_buffer <wchar_t>::const_iterator i = last_characters.begin ();
		std::wstring::const_iterator j = end_token.begin ();
		while (result && i != last_characters.end () && j != end_token.end ())
		{
			result = *i == *j;
			++i;
			++j;
		}
	}
	return result;
}

void mu::io::lexer::complex_identifier::lex (wchar_t character)
{
	if (character != L'\uffff')
	{
		if (!have_end_token)
		{
			switch (character)
			{
			case L'|':
				have_end_token = true;
				last_characters.resize (end_token.size ());
				break;
			default:
				end_token.push_back (character);
				break;
			}
		}
		else
		{		
			last_characters.push_back (character);
			last = lexer.position;
			data.push_back (character);
		}
		if (have_end_token && match ())
		{
			data.resize (data.size () - end_token.size ());
			mu::io::tokens::identifier * token (new mu::io::tokens::identifier (data));
			lexer.target (token, mu::core::context (first, lexer.position));
			lexer.state.pop ();
		}
	}
	else
	{
		std::wstring message (L"End of file while parsing complex identifier");
		(*lexer.errors) (message, mu::core::context (lexer.position, lexer.position));
		auto error (boost::shared_ptr <mu::io::lexer::state> (new mu::io::lexer::error));
		lexer.state.push (error);
	}
}
