//
//  finished.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{
    namespace parser
    {
        class finished : public ::lambda_p::parser::state
        {
        public:
            state_id state_type ();
        };
    }
}