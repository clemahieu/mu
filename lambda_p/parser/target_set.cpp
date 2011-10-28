#include "target_set.h"

#include <lambda_p/core/statement.h>

lambda_p::parser::target_set::target_set (lambda_p::core::statement & statement_a)
	: statement (statement_a)
{
}

void lambda_p::parser::target_set::operator () (size_t declaration)
{
	statement.target = declaration;
}