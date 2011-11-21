#include <lambda_p/parser/association.h>

#include <lambda_p/parser/association_target.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/tokens/token.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/data.h>

#include <sstream>

lambda_p::parser::association::association (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target_a)
	: on_results (false),
	target (target_a),
	routine (routine_a),
	parser (parser_a)
{
}

boost::function <void (size_t)> lambda_p::parser::association::sink_data ()
{
	boost::function <void (size_t)> result (target.sink_argument ());
	return result;
}

void lambda_p::parser::association::parse (lambda_p::tokens::token * token)
{	
	lambda_p::tokens::token_ids token_id (token->token_id ());
	if (on_results)
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
				auto identifier (static_cast <lambda_p::tokens::identifier *> (token));
				auto j = parser.keywords.find (identifier->string);
				if (j == parser.keywords.end ())
				{
					auto i = routine.positions.find (identifier->string);
					if (i == routine.positions.end ())
					{
						auto location (target.sink_declaration ());
						size_t declaration (routine.routine_m->add_declaration ());
						location (declaration);
						routine.positions [identifier->string] = declaration;
						for (auto i = routine.unresolved_references.find (identifier->string); i != routine.unresolved_references.end (); ++i)
						{
							i->second (declaration);
						}
						routine.unresolved_references.erase (identifier->string);
					}
					else
					{
						std::wstring message (L"Identifier already used: ");
						message.append (identifier->string);
						boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
						parser.state.push (new_state);
					}
				}
				else
				{
					std::wstringstream message;					
					message << L"Cannot use: ";
					message << identifier->string;
					message << L" as an identifier, it's a keyword";
					parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
				}
			}
			break;
		case lambda_p::tokens::token_id_divider:
            parser.state.pop ();
			break;
		default:
			std::wstring message (L"Looking for identifiers while parsing statement results");
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			parser.state.push (new_state);
			break;
		}
	}
	else
	{
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
				auto identifier (static_cast <lambda_p::tokens::identifier *> (token));
				auto i = routine.positions.find (identifier->string);
				auto location (target.sink_argument ());
				if (i != routine.positions.end ())
				{
					location (i->second);
				}
				else
				{
					routine.unresolved_references.insert (std::multimap <std::wstring, boost::function <void (size_t)>>::value_type (identifier->string, location));
				}
			}
			break;
		case lambda_p::tokens::token_id_data:
			{
				boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::data (parser, routine, *this));
				parser.state.push (new_state);
			}
			break;
		case lambda_p::tokens::token_id_divider:			
			on_results = true;
			break;
		default:
			std::wstring message (L"Invalid statement argument: ");
			message.append (parser.token_type_name (token));
			boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			parser.state.push (new_state);
			break;
		}
	}
}