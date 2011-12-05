#include "expression.h"

#include <lambda_p/tokens/token.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/core/expression.h>
#include <lambda_p/tokens/identifier.h>

#include <sstream>

#include <boost/bind.hpp>

lambda_p::parser::expression::expression (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, boost::function <void (lambda_p::core::expression * expression)> target_a)
	: target (target_a),
	parser (parser_a),
	routine (routine_a),
	has_nested_expression (false),
	is_naming (false)
{
}
			
void lambda_p::parser::expression::parse (lambda_p::tokens::token * token)
{	
	lambda_p::tokens::token_ids token_id (token->token_id ());
	switch (token_id)
	{
		case lambda_p::tokens::token_id_divider:
			if (is_naming)
			{
				std::wstringstream message;
				message << L"Expecting expression list, have divider";
				parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
			}
			else if (has_nested_expression)
			{
				std::wstringstream message;
				message << L"Left had side of naming must be an identifier list";				
				parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));
			}
			else
			{
				is_naming = true;
				for (auto i = local_unresolved.begin (); i != local_unresolved.end (); ++i)
				{
					auto existing (routine.names.find (i->first));
					if (existing == routine.names.end ())
					{
						routine.names.insert (std::map <std::wstring, lambda_p::core::expression *>::value_type (i->first, new lambda_p::core::expression));
					}
					else
					{
						std::wstringstream message;
						message << L"Identifier: ";
						message << i->first;
						message << L" has already been defined";
						parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::error (message.str ())));						
					}
				}
				local_unresolved.clear ();
			}
			break;
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			auto identifier (static_cast <lambda_p::tokens::identifier *> (token));
			local_unresolved.insert (std::map <std::wstring, size_t>::value_type (identifier->string, expressions.size ()));
			expressions.push_back (nullptr);
			break;
		case lambda_p::tokens::token_id_left_square:
			has_nested_expression = true;
			parser.state.push (boost::shared_ptr <lambda_p::parser::expression> (new lambda_p::parser::expression (parser, routine, boost::bind <void> (&lambda_p::parser::expression::nested_expression_sink, this, _1))));
			break;
		case lambda_p::tokens::token_id_right_square:
			auto expression (new lambda_p::core::expression);
			expression.contents.insert (expressions.begin (), expressions.end ());
			target (
			parser.state.pop ();
			break;
	}
}

void lambda_p::parser::expression::nested_expression_sink (lambda_p::core::expression * expression_a)
{
	expressions.push_back (expression_a);
}