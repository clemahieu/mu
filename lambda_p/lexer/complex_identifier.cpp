#include <lambda_p/lexer/complex_identifier.h>

#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/lexer/lexer.h>
#include <lambda_p/lexer/error.h>

lambda_p::lexer::complex_identifier::complex_identifier (lambda_p::lexer::lexer & lexer_a)
	: have_end_token (false),
	lexer (lexer_a)
{
}

lambda_p::lexer::state_id lambda_p::lexer::complex_identifier::state_type ()
{
	return lambda_p::lexer::state_complex_identifier;
}

bool lambda_p::lexer::complex_identifier::match ()
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

void lambda_p::lexer::complex_identifier::lex (wchar_t character)
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
			data.push_back (character);
		}
		if (have_end_token && match ())
		{
			data.resize (data.size () - end_token.size ());
			lambda_p::tokens::complex_identifier * token (new lambda_p::tokens::complex_identifier (data, end_token));
			lexer.target (token);
			lexer.state.pop ();
		}
	}
	else
	{
		std::wstring message (L"End of file while parsing complex identifier");
		auto error (boost::shared_ptr <lambda_p::lexer::state> (new lambda_p::lexer::error (message)));
		lexer.state.push (error);
	}
}