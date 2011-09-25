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
	namespace binder
	{
		class routine_binder;
	}
    namespace core
    {
        class routine;
        class declaration;
        class reference : public node
        {
            template <typename> friend class ::lambda_p::serialization::simple;
			friend class ::lambda_p::binder::routine_binder;
            friend class ::lambda_p::core::routine;
        public:
            reference ();
            reference (::lambda_p::core::declaration * declaration_a);
            ~reference ();
			node_id node_type () const;
			::std::wstring node_type_name () const;
		private:
            ::lambda_p::core::declaration * declaration;
        };
    }
}