//
//  undefined_reference.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/errors/undefined_reference.h>

::lambda_p::errors::error_id lambda_p::errors::undefined_reference::error_type ()
{
    return ::lambda_p::errors::error_undefined_reference;
}

lambda_p::errors::undefined_reference::undefined_reference (::lambda_p::core::position position_a)
: position (position_a)
{
}

void lambda_p::errors::undefined_reference::string (::std::wostream & stream)
{
    stream << L"Undefined reference from statement: ";
    stream << position.statement;
    stream << L" argument: ";
    stream << position.argument;
}