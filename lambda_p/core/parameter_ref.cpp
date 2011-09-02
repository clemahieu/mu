//
//  parameter_ref.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/core/parameter_ref.h>

#include <lambda_p/core/routine.h>

lambda_p::core::parameter_ref::parameter_ref (::lambda_p::core::routine * routine_a, size_t target_parameter_a, size_t self_statement_a, size_t self_argument_a)
: routine (routine_a),
target_parameter (target_parameter_a),
self_statement (self_statement_a),
self_argument (self_argument_a)
{
}

lambda_p::core::parameter_ref::~parameter_ref ()
{
}

void lambda_p::core::parameter_ref::validate (::std::iostream & problems) const
{
	size_t parameters_count (routine->parameters);
    bool valid (parameters_count > target_parameter);
	if (valid)
	{
		validate_argument ("parameter_ref: ", routine, self_statement, self_argument, problems);
	}
	else
	{
		problems << "parameter_ref: ";
		problems << this;
		problems << " referencing routine: ";
		problems << &routine;
		problems << " references a parameter: ";
		problems << target_parameter;
		problems << " that is greater than the max: ";
		problems << parameters_count - 1;
		problems << "\n";
	}
}