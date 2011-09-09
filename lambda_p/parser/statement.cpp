#include "statement.h"

#include <lambda_p/parser/body.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>

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

void lambda_p::parser::statement::sink_reference (::lambda_p::parser::reference_identifiers reference)
{
	size_t current_statement (statement_m->routine->statements.size () - 1);
	size_t current_argument (statement_m->routine->statements [current_statement]->arguments.size ());
	::std::map < ::lambda_p::parser::reference_identifiers, ::lambda_p::parser::reference_position>::iterator search = body->positions.find (reference);
	if (search != body->positions.end ())
	{
		::lambda_p::core::reference * ref = routine ()->add_result_ref (search->second.statement, search->second.argument, current_statement, current_argument);
		statement_m->add_argument (ref);
	}
	else
	{
		::lambda_p::core::reference * ref = routine ()->add_result_ref (-1, -1, current_statement, current_argument);
		statement_m->add_argument (ref);
		body->unresolved_references.insert (::std::multimap < ::lambda_p::parser::reference_identifiers, ::lambda_p::core::reference *>::value_type (reference, ref));
	}
}