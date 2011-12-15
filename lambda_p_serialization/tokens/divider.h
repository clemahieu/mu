//
//  statement_end.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p_serialization/tokens/token.h>

#include <string>

namespace lambda_p_serialization
{
    namespace tokens
    {
        class divider : public lambda_p_serialization::tokens::token
        {
			lambda_p_serialization::tokens::token_ids token_id () override;
			std::wstring token_name () override;
        };
    }
}