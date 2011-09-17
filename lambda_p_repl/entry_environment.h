//
//  entry_environment.h
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
    namespace core
    {
        class routine;
        class node;
    }
}
namespace lambda_p_repl
{
    class repl_quit;
    class entry_environment
    {
    public:
        entry_environment (::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit_binder_a);
        entry_environment ();
        void operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
		::lambda_p::core::node * environment_node (::boost::shared_ptr < ::lambda_p::core::routine> routine);
    private:
		::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit;
    };
}