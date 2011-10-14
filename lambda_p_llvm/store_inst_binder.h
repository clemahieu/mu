//
//  store_binder.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p
{
	namespace binder
	{
		class routine_instances;
	}
}
namespace lambda_p_llvm
{
    class generation_context;
    class store_inst_binder : public ::lambda_p::binder::binder
    {
    public:
        store_inst_binder (::lambda_p_llvm::generation_context & context_a);
        void bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
    private:
        ::lambda_p_llvm::generation_context & context;
    };
}