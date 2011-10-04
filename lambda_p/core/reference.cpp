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

lambda_p::core::reference::reference ()
{
}

lambda_p::core::reference::reference (::lambda_p::core::declaration * declaration_a)
: declaration (declaration_a)
{
}

lambda_p::core::reference::~reference ()
{
}

::lambda_p::core::node_id lambda_p::core::reference::node_type () const
{
	return ::lambda_p::core::node_reference;
}