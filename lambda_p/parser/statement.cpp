#include "statement.h"

#include <lambda_p/parser/body.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/simple_parser.h>

lambda_p::parser::statement::statement (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a)
	: body (body_a),
	have_target (false),
	on_results (false),
	routine (routine_a),
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