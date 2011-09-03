//
//  error.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p/tokens/error.h>

lambda_p::tokens::error::error (::std::wstring message_a)
: message (message_a)
{
}

size_t lambda_p::tokens::error::token_id ()
{
	return ::lambda_p::tokens::token_ids::token_id_error;
}