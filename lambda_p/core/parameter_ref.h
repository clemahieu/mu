//
//  parameter_ref.h
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <cstring>

#include <lambda_p/core/node.h>

namespace lambda_p
{
    namespace core
    {
        class routine;
        class parameter_ref : public node
        {
        public:
            parameter_ref (::lambda_p::core::routine & routine_a);
            ~parameter_ref ();
            bool valid ();
            ::lambda_p::core::routine & routine;
            size_t index;
        };
    }
}