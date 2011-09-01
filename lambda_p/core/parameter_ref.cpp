//
//  parameter_ref.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/core/parameter_ref.h>

#include <lambda_p/core/routine.h>

lambda_p::core::parameter_ref::parameter_ref (::lambda_p::core::routine & routine_a)
: routine (routine_a)
{
}

lambda_p::core::parameter_ref::~parameter_ref ()
{
}

bool lambda_p::core::parameter_ref::valid ()
{
    bool result (routine.parameters > index);
    return result;
}