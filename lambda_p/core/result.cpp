#include "result.h"

#include <iostream>

#include <lambda_p/core/routine.h>

lambda_p::core::result::result(::lambda_p::core::routine * routine_a, size_t statement_a, size_t index_a)
	: routine (routine_a),
	statement (statement_a),
	index (index_a)
{
}

lambda_p::core::result::~result(void)
{
}

void lambda_p::core::result::validate (::std::iostream & problems)
{
	size_t statement_size (routine->statements.size ());
	if (statement_size > statement)
	{
		size_t arguments_size (routine->statements [statement].arguments.size ());
		if (arguments_size > index)
		{
            if (routine->statements [statement].arguments [index] == this)
            {
            }
            else
            {
                problems << "result: ";
                problems << this;
                problems << " referencing routine: ";
                problems << &routine;
                problems << " referencing statement: ";
                problems << statement;
                problems << " referencing argument: ";
                problems << index;
                problems << " is referencing an object that is not this\n";
            }
		}
		else
		{
			problems << "result: ";
			problems << this;
			problems << " referencing routine: ";
			problems << &routine;
			problems << " referencing statement: ";
			problems << statement;
			problems << " references an argument: ";
			problems << index;
			problems << " that is greater than the max: ";
			problems << arguments_size;
			problems << "\n";
		}
	}
	else
	{
		problems << "result: ";
		problems << this;
		problems << " referencing routine: ";
		problems << &routine;
		problems << " references a statement: ";
		problems << statement;
		problems << " that is greater than the max: ";
		problems << statement_size - 1;
		problems << "\n";
	}
}