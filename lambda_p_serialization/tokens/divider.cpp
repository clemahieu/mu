//
//  statement_end.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p_serialization/tokens/visitor.h>

std::wstring lambda_p_serialization::tokens::divider::token_name ()
{
	return std::wstring (L"divider");
}

void lambda_p_serialization::tokens::divider::operator () (lambda_p_serialization::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}