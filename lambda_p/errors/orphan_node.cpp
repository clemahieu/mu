//
//  orphan_node.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/errors/orphan_node.h>

::lambda_p::errors::error_id lambda_p::errors::orphan_node::error_type ()
{
    return ::lambda_p::errors::error_orphan_node;
}

lambda_p::errors::orphan_node::orphan_node (::lambda_p::core::position position_a)
: position (position_a)
{
}

void lambda_p::errors::orphan_node::string (::std::wostream & stream)
{
    stream << L"Orphan node at statement: ";
    stream << position.statement;
    stream << L" argument: ";
    stream << position.argument;
}