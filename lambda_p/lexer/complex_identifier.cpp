#include <lambda_p/lexer/complex_identifier.h>

lambda_p::lexer::complex_identifier::complex_identifier(void)
	: have_end_token (false)
{
}

lambda_p::lexer::complex_identifier::~complex_identifier(void)
{
}

::lambda_p::lexer::state_id lambda_p::lexer::complex_identifier::state_type ()
{
	return ::lambda_p::lexer::state_complex_identifier;
}

bool lambda_p::lexer::complex_identifier::match ()
{
	bool result (last_characters.size () == end_token.size ());
	if (result)
	{
		::boost::circular_buffer <wchar_t>::const_iterator i = last_characters.begin ();
		::std::wstring::const_iterator j = end_token.begin ();
		while (result && i != last_characters.end () && j != end_token.end ())
		{
			result = *i == *j;
			++i;
			++j;
		}
	}
	return result;
}