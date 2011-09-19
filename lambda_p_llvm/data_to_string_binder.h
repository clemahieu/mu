#pragma once

#include <lambda_p/binder/node_binder.h>
#include <lambda_p_llvm/llvm_generation_context.h>

namespace lambda_p_llvm
{
    class llvm_generation_context;
    class data_to_string_binder : public ::lambda_p::binder::node_binder
    {
    public:
        data_to_string_binder (::lambda_p_llvm::llvm_generation_context context_a);
        ~data_to_string_binder (void);
        void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);			
        void operator () ();
        ::lambda_p_llvm::llvm_generation_context context;
    };
}

