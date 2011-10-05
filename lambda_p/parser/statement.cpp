#include "statement.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/simple_parser.h>
#include <lambda_p/core/association.h>

lambda_p::parser::statement::statement (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a)
	: have_target (false),
	on_results (true),
	routine (routine_a),
	statement_m (routine->routine_m->add_statement (NULL))
{
}

lambda_p::parser::statement::~statement(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::statement::state_type ()
{
	return lambda_p::parser::state_statement;
}

void lambda_p::parser::statement::sink_result (::lambda_p::core::node * declaration)
{
	statement_m->association->results.push_back (declaration);
}

void lambda_p::parser::statement::sink_argument (::lambda_p::core::node * argument)
{
	statement_m->association->parameters.push_back (argument);
}