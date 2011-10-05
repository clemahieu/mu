//
//  load_binder.h
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
    class load_inst_binder : public ::lambda_p::binder::node_binder
    {
    public:  
        load_inst_binder (::lambda_p_llvm::generation_context & context_a);
        void bind (::lambda_p::core::statement * statement, ::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
    private:
        ::lambda_p_llvm::generation_context & context;
    };
}
