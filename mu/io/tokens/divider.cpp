//
//  statement_end.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/visitor.h>

std::wstring mu::io::tokens::divider::token_name ()
{
	return std::wstring (L"divider");
}

void mu::io::tokens::divider::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}