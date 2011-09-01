//
//  argument_ref.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/core/argument_ref.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>

lambda_p::core::results_ref::results_ref (::lambda_p::core::routine & routine_a)
: routine (routine_a)
{
}

lambda_p::core::results_ref::~results_ref ()
{
}

bool lambda_p::core::results_ref::valid ()
{
    bool result (routine.body.size () > statement);
    if (result)
    {
        result = routine.body [statement].results > index;
    }
    
    return result;
}