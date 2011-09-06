#include "statement.h"

lambda_p::serialization::parser::statement::statement(size_t statement_number_a, ::std::wstring statement_name_a, ::boost::shared_ptr < ::std::map < ::lambda_p::serialization::parser::result_reference, ::lambda_p::serialization::parser::result_position> > positions_a)
	: statement_name (statement_name_a),
	positions (positions_a),
	statement_number (statement_number_a),
	argument_count (0),
	have_target (false)
{
}

lambda_p::serialization::parser::statement::~statement(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::statement::state_type ()
{
	return lambda_p::serialization::parser::state_statement;
}
