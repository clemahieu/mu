#include "statement.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/core/association.h>
#include <lambda_p/parser/position_set.h>

#include <boost/bind.hpp>

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