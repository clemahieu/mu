//
//  abort_binder.h
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/node_binder.h>

namespace llvm
{
    class Function;
}
namespace lambda_p_llvm
{
    class generation_context;
    class abort_binder : public ::lambda_p::binder::node_binder
    {
    public:  
        abort_binder (::llvm::Function * abort_function_a, ::lambda_p_llvm::generation_context * context_a);
        void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
        void operator () ();
    private:
        ::llvm::Function * abort_function;
        ::lambda_p_llvm::generation_context * context;
    };
}