#include <mu/io/lexer/complex_identifier.h>

#include <mu/io/tokens/identifier.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/lexer/error.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/lexer/context.h>

#include <gc_cpp.h>

mu::io::lexer::complex_identifier::complex_identifier (mu::io::lexer::lexer & lexer_a, mu::io::debugging::position first_a)
	: have_end_token (false),
	first (first_a),
	lexer (lexer_a)
{
}

bool mu::io::lexer::complex_identifier::match ()
{
	bool result (last_characters.size () == end_token.size ());
	if (result)
	{
		boost::circular_buffer <char32_t>::const_iterator i = last_characters.begin ();
		mu::string::const_iterator j = end_token.begin ();
		while (result && i != last_characters.end () && j != end_token.end ())
		{
			result = *i == *j;
			++i;
			++j;
		}
	}
	return result;
}

void mu::io::lexer::complex_identifier::lex (mu::io::lexer::context const & context_a)
{
	if (context_a.character != U'\U0000FFFF')
	{
		if (!have_end_token)
		{
			switch (context_a.character)
			{
			case L'}':
				have_end_token = true;
				last_characters.resize (end_token.size ());
				break;
			default:
				end_token.push_back (context_a.character);
				break;
			}
		}
		else
		{		
			last_characters.push_back (context_a.character);
			data.push_back (context_a.character);
		}
		if (have_end_token && match ())
		{
			data.resize (data.size () - end_token.size ());
			mu::io::tokens::identifier * token (new (GC) mu::io::tokens::identifier (data));
			lexer.target (token, mu::io::debugging::context (first, context_a.position));
			lexer.state.pop ();
		}
	}
	else
	{
		mu::string message (U"End of file while parsing complex identifier");
		(*lexer.errors) (message);
		auto error (new (GC) mu::io::lexer::error);
		lexer.state.push (error);
	}
}
