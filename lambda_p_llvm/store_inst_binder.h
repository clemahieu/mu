//
//  store_binder.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p_llvm
{
    class generation_context;
    class store_inst_binder : public ::lambda_p::binder::node_binder
    {
    public:
        store_inst_binder (::lambda_p_llvm::generation_context & context_a);
        void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
    private:
        ::lambda_p_llvm::generation_context & context;
    };
}