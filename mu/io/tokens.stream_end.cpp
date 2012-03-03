//
//  stream_end.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <mu/io/tokens.stream_end.h>
#include <mu/io/tokens.visitor.h>

std::wstring mu::io::tokens::stream_end::token_name ()
{
	return std::wstring (L"stream end");
}

void mu::io::tokens::stream_end::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}
