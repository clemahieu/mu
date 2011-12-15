//
//  statement_end.cpp
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_serialization/tokens/divider.h>

lambda_p_serialization::tokens::token_ids lambda_p_serialization::tokens::divider::token_id ()
{
	return lambda_p_serialization::tokens::token_id_divider;
}

std::wstring lambda_p_serialization::tokens::divider::token_name ()
{
	return std::wstring (L"divider");
}