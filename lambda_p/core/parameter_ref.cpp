//
//  parameter_ref.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/core/parameter_ref.h>

#include <lambda_p/core/routine.h>

lambda_p::core::parameter_ref::parameter_ref (::lambda_p::core::routine * routine_a, size_t index_a)
: routine (routine_a),
index (index_a)
{
}

lambda_p::core::parameter_ref::~parameter_ref ()
{
}

void lambda_p::core::parameter_ref::validate (::std::iostream & problems)
{
    bool valid (routine->parameters > index);
	if (valid)
	{
	}
	else
	{
		problems << "parameter_ref :";
		problems << this;
		problems << " referencing routine:";
		problems << &routine;
		problems << " references a parameter: ";
		problems << index;
		problems << " that is greater than the max: ";
		problems << routine->parameters - 1;
		problems << "\n";
	}
}