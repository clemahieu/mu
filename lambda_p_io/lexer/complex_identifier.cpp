#include <lambda_p_io/lexer/complex_identifier.h>

#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/lexer/error.h>
#include <lambda_p/errors/error_target.h>

lambda_p_io::lexer::complex_identifier::complex_identifier (lambda_p_io::lexer::lexer & lexer_a)
	: have_end_token (false),
	lexer (lexer_a),
	first (lexer_a.position),
	last (lexer_a.position)
{
}

bool lambda_p_io::lexer::complex_identifier::match ()
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

void lambda_p_io::lexer::complex_identifier::lex (wchar_t character)
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
			lambda_p_io::tokens::identifier * token (new lambda_p_io::tokens::identifier (data));
			lexer.target (token, lambda_p::context (first, lexer.position));
			lexer.state.pop ();
		}
	}
	else
	{
		std::wstring message (L"End of file while parsing complex identifier");
		(*lexer.errors) (message);
		auto error (boost::shared_ptr <lambda_p_io::lexer::state> (new lambda_p_io::lexer::error));
		lexer.state.push (error);
	}
}
