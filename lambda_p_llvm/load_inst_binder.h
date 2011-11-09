//
//  load_binder.h
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
		class list;
	}
}
namespace lambda_p_llvm
{
    class generation_context;
    class load_inst_binder : public lambda_p::binder::binder
    {
    public:  
        void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
    };
}
