#include "statement.h"

#include <lambda_p/parser/body.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/simple_parser.h>

lambda_p::parser::statement::statement(::boost::shared_ptr < ::lambda_p::parser::body> body_a, ::std::wstring statement_name_a)
	: statement_name (statement_name_a),
	body (body_a),
	have_target (false),
	have_argument (false),
	statement_m (body_a->routine ()->add_statement ())
{
}

lambda_p::parser::statement::~statement(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::statement::state_type ()
{
	return lambda_p::parser::state_statement;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::parser::statement::routine ()
{
	return body->routine ();
}

void lambda_p::parser::statement::sink_reference (::lambda_p::parser::simple_parser & parser, ::lambda_p::parser::reference_identifiers reference)
{
	::std::map < ::lambda_p::parser::reference_identifiers, ::lambda_p::core::declaration *>::iterator search = body->positions.find (reference);
	if (search != body->positions.end ())
	{
		::lambda_p::core::reference * ref = routine ()->add_reference (search->second);
		statement_m->add_argument (ref);
	}
	else
	{
		::lambda_p::core::reference * ref = routine ()->add_reference (NULL);
		statement_m->add_argument (ref);
		body->unresolved_references.insert (::std::multimap < ::lambda_p::parser::reference_identifiers, ::lambda_p::core::reference *>::value_type (reference, ref));
	}
}

void lambda_p::parser::statement::sink_data (::lambda_p::parser::simple_parser & parser, ::lambda_p::tokens::identifier * identifier)
{
	statement_m->add_argument (routine ()->add_data (identifier->string));
}

void lambda_p::parser::statement::sink_declaration (::lambda_p::parser::simple_parser & parser, ::lambda_p::tokens::identifier * identifier)
{
	::lambda_p::parser::reference_identifiers reference (statement_name, identifier->string);
    ::lambda_p::core::declaration * declaration (routine ()->add_declaration ());
	body->positions [reference] = declaration;
	statement_m->add_argument (declaration);
}