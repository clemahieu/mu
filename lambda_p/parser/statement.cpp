#include "statement.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/core/association.h>
#include <lambda_p/parser/position_set.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/parser/association.h>
#include <lambda_p/parser/target_set.h>

#include <boost/bind.hpp>

lambda_p::parser::statement::statement (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a)
	: have_target (false),
	on_results (true),
	routine (routine_a),
	statement_m (routine.routine_m->add_statement ()),
	parser (parser_a)
{
}

void lambda_p::parser::statement::parse (lambda_p::tokens::token * token)
{				
	if (have_target)
	{
		parser.state.pop ();
		parser (token);
	} 
	else
	{
		lambda_p::tokens::token_ids token_id (token->token_id ());
		switch (token_id)
		{
		case lambda_p::tokens::token_id_complex_identifier:
		case lambda_p::tokens::token_id_identifier:
			{
                have_target = true;
				lambda_p::tokens::identifier * identifier (static_cast < lambda_p::tokens::identifier *> (token));
				auto i = routine.positions.find (identifier->string);
				if (i != routine.positions.end ())
				{
					statement_m->target = i->second;
				}
				else
				{
					routine.unresolved_references.insert (std::multimap <std::wstring, boost::function <void (size_t)>>::value_type (identifier->string, boost::bind <void> (lambda_p::parser::target_set (*statement_m), _1)));
				}
				parser.state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::association (parser, routine, *this)));
			}
			break;
		default:
			std::wstring message (L"Looking for identifier while parsing target of statement");
			boost::shared_ptr < lambda_p::parser::state> new_state (new lambda_p::parser::error (message));
			parser.state.push (new_state);
			break;
		}
	}
}

boost::function <void (size_t)> lambda_p::parser::statement::sink_declaration ()
{
	statement_m->association->declarations.push_back (~0);
	boost::function <void (size_t)> result (boost::bind <void> (lambda_p::parser::position_set (statement_m->association->declarations, statement_m->association->declarations.size () - 1), _1));
	return result;
}

boost::function <void (size_t)> lambda_p::parser::statement::sink_argument ()
{
	statement_m->association->references.push_back (~0);
	boost::function <void (size_t)> result (boost::bind <void> (lambda_p::parser::position_set (statement_m->association->references, statement_m->association->references.size () - 1), _1));
	return result;
}