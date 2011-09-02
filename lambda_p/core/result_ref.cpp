//
//  argument_ref.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/core/result_ref.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/result.h>

lambda_p::core::result_ref::result_ref (::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a, size_t target_statement_a, size_t target_argument_a)
: routine (routine_a),
self_statement (self_statement_a),
self_argument (self_argument_a)
{
}

lambda_p::core::result_ref::~result_ref ()
{
}

void lambda_p::core::result_ref::validate (::std::iostream & problems)
{
	size_t statements_size (routine->statements.size ());
    bool valid (statements_size > self_statement);
    if (valid)
    {
		size_t arguments_size (routine->statements [self_statement].arguments.size ());
		valid = arguments_size > self_argument;
		if (valid)
		{
            if (routine->statements [self_statement].arguments [self_argument] == this)
			{
			}
			else
			{				
				problems << "result_ref: ";
				problems << this;
				problems << " referencing routine: ";
				problems << &routine;
				problems << " referencing statement: ";
				problems << self_statement;
				problems << " referencing argument: ";
				problems << self_argument;
				problems << " references a node that is not this\n";
			}
		}
		else
		{
			problems << "result_ref: ";
			problems << this;
			problems << " referencing routine: ";
			problems << &routine;
			problems << " referencing statement: ";
			problems << self_statement;
			problems << " references an argument: ";
			problems << self_argument;
			problems << " that is greater than the max: ";
			problems << arguments_size - 1;
			problems << "\n";
		}
    }
	else
	{
		problems << "result_ref: ";
		problems << this;
		problems << " referencing routine: ";
		problems << &routine;
		problems << " references a statement: ";
		problems << self_statement;
		problems << " that is greater than the max: ";
		problems << statements_size - 1;
		problems << "\n";
	}
}