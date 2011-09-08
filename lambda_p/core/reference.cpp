//
//  argument_ref.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/core/reference.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/declaration.h>

lambda_p::core::reference::reference (::lambda_p::core::routine * routine_a, size_t target_statement_a, size_t target_argument_a, size_t self_statement_a, size_t self_argument_a)
: routine (routine_a),
self_statement (self_statement_a),
self_argument (self_argument_a),
target_statement (target_statement_a),
target_argument (target_argument_a)
{
}

lambda_p::core::reference::~reference ()
{
}

void lambda_p::core::reference::validate (::std::iostream & problems) const
{
	size_t statements_size (routine->statements.size ());
    bool valid (statements_size > target_statement);
    if (valid)
    {
		size_t arguments_size (routine->statements [target_statement]->arguments.size ());
		valid = arguments_size > target_argument;
		if (valid)
		{
			if (routine->statements [target_statement]->arguments [target_argument]->node_type () == ::lambda_p::core::node_result)
			{
				validate_argument ("result_ref: ", routine, self_statement, self_argument, problems);
			}
			else
			{				
				problems << "result_ref: ";
				problems << this;
				problems << " referencing routine: ";
				problems << &routine;
				problems << " referencing statement: ";
				problems << target_statement;
				problems << " referencing argument: ";
				problems << target_argument;
				problems << " references a node that is not a result\n";
			}
		}
		else
		{
			problems << "result_ref: ";
			problems << this;
			problems << " referencing routine: ";
			problems << &routine;
			problems << " referencing statement: ";
			problems << target_statement;
			problems << " references an argument: ";
			problems << target_argument;
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
		problems << target_statement;
		problems << " that is greater than the max: ";
		problems << statements_size - 1;
		problems << "\n";
	}
}

::lambda_p::core::node_id lambda_p::core::reference::node_type () const
{
	return ::lambda_p::core::node_result_ref;
}