//
//  stream_end.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/tokens/token.h>

namespace lambda_p
{
    namespace tokens
    {
        class stream_end : public ::lambda_p::tokens::token
        {
        public:
            token_ids token_id ();
        };
    }
}
