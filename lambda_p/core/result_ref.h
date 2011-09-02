//
//  argument_ref.h
//  lambda_p
//
//  Created by Colin LeMahieu on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <cstring>
#include <iostream>

#include <lambda_p/core/node.h>

namespace lambda_p
{
    namespace serialization
    {
        template <typename> class simple;
    }
    namespace core
    {
        class routine;
        class result_ref : public node
        {
            template <typename> friend class ::lambda_p::serialization::simple;
        public:
            result_ref (::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a, size_t target_statement_a, size_t target_argument_a);
            ~result_ref ();
            void validate (::std::iostream & problems);
		private:
            ::lambda_p::core::routine * routine;
            size_t self_statement;
            size_t self_argument;
            size_t target_statement;
            size_t target_argument;
        };
    }
}