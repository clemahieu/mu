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

lambda_p::core::result_ref::result_ref (::lambda_p::core::routine & routine_a, size_t statement_a, size_t index_a)
: routine (routine_a),
statement (statement_a),
index (index_a)
{
}

lambda_p::core::result_ref::~result_ref ()
{
}

void lambda_p::core::result_ref::validate (::std::iostream & problems)
{
	size_t statements_size (routine.statements.size ());
    bool valid (statements_size > statement);
    if (valid)
    {
		size_t arguments_size (routine.statements [statement].arguments.size ());
		valid = arguments_size > index;
		if (valid)
		{
			valid = dynamic_cast < ::lambda_p::core::result *> (routine.statements [statement].arguments [index]) != NULL;
			if (valid)
			{
			}
			else
			{				
				problems << "result_ref: ";
				problems << this;
				problems << " referencing routine: ";
				problems << &routine;
				problems << " referencing statement: ";
				problems << statement;
				problems << " referencing argument: ";
				problems << index;
				problems << " references a node that is not actually a result object\n";
			}
		}
		else
		{
			problems << "result_ref: ";
			problems << this;
			problems << " referencing routine: ";
			problems << &routine;
			problems << " referencing statement: ";
			problems << statement;
			problems << " references an argument: ";
			problems << index;
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
		problems << statement;
		problems << " that is greater than the max: ";
		problems << statements_size - 1;
		problems << "\n";
	}
}