//
//  stream_end.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_io/tokens/stream_end.h>
#include <lambda_p_io/tokens/visitor.h>

std::wstring lambda_p_io::tokens::stream_end::token_name ()
{
	return std::wstring (L"stream end");
}

void lambda_p_io::tokens::stream_end::operator () (lambda_p_io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}