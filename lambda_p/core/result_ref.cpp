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

lambda_p::core::result_ref::result_ref (::lambda_p::core::routine & routine_a)
: routine (routine_a)
{
}

lambda_p::core::result_ref::~result_ref ()
{
}

bool lambda_p::core::result_ref::valid ()
{
    bool result (routine.statements.size () > statement);
    if (result)
    {
		result = routine.statements [statement].arguments.size () > index;
		if (result)
		{
			result = dynamic_cast < ::lambda_p::core::result *> (routine.statements [statement].arguments [index]) != NULL;
		}
    }
    
    return result;
}