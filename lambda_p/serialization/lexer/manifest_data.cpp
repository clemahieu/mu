#include "manifest_data.h"

lambda_p::serialization::lexer::manifest_data::manifest_data(void)
	: have_end_token (false)
{
}

lambda_p::serialization::lexer::manifest_data::~manifest_data(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::manifest_data::state_type ()
{
	return ::lambda_p::serialization::lexer::state_id::state_manifest_data;
}

bool lambda_p::serialization::lexer::manifest_data::match ()
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