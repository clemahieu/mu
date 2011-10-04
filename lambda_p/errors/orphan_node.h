//
//  orphan_node.h
//  lambda_p
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/errors/error.h>
#include <lambda_p/core/position.h>

namespace lambda_p
{
    namespace errors
    {
        class orphan_node : public ::lambda_p::errors::error
        {
        public:
            orphan_node (::lambda_p::core::position position_a);
            error_id error_type ();
            void string (::std::wostream & stream);
            ::lambda_p::core::position position;
        };
    }
}