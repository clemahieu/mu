#include "unresolved_statement.h"

lambda_p::errors::unresolved_statement::unresolved_statement (size_t statement_number_a)
	: statement_number (statement_number_a)
{
}

::lambda_p::errors::error_id lambda_p::errors::unresolved_statement::error_type ()
{
	return ::lambda_p::errors::error_unresolved_statement;
}

void lambda_p::errors::unresolved_statement::string (::std::wostream & stream)
{
	stream << L"Unresolved statement number: ";
	stream << statement_number;
}