#include "statement.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/core/association.h>

lambda_p::parser::statement::statement (boost::shared_ptr < lambda_p::parser::routine> routine_a)
	: have_target (false),
	on_results (true),
	routine (routine_a),
	statement_m (routine->routine_m->add_statement ())
{
}

lambda_p::parser::statement::~statement(void)
{
}

lambda_p::parser::state_id lambda_p::parser::statement::state_type ()
{
	return lambda_p::parser::state_statement;
}

lambda_p::parser::declaration_location lambda_p::parser::statement::sink_declaration ()
{
	statement_m->association->results.push_back (~0);
	lambda_p::parser::declaration_location result (statement_m->association->results, statement_m->association->results.size () - 1);
	return result;
}

lambda_p::parser::declaration_location lambda_p::parser::statement::sink_argument ()
{
	statement_m->association->parameters.push_back (~0);
	lambda_p::parser::declaration_location result (statement_m->association->parameters, statement_m->association->parameters.size () - 1);
	return result;
}