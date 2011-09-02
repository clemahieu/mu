#include "result.h"

#include <iostream>

#include <lambda_p/core/routine.h>

lambda_p::core::result::result(::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a)
	: routine (routine_a),
	self_statement (self_statement_a),
	self_argument (self_argument_a)
{
}

lambda_p::core::result::~result(void)
{
}

void lambda_p::core::result::validate (::std::iostream & problems) const
{
	validate_argument ("result: ", routine, self_statement, self_argument, problems);
}