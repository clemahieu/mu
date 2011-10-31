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
    }
}
namespace lambda_p_llvm
{
	class context;
	class generation_context;
}
namespace lambda_p_repl
{
    class repl;
    class entry_environment
    {
    public:
		entry_environment (lambda_p_repl::repl * repl_a);
        entry_environment ();
        void operator () (boost::shared_ptr <lambda_p_llvm::context> context_instance, lambda_p_llvm::generation_context & context, boost::shared_ptr <lambda_p::core::routine> routine_a);
		size_t environment_node (boost::shared_ptr < lambda_p::core::routine> routine);
    private:
        static void quit_invoke (void * object);
		lambda_p_repl::repl * repl;
    };
}