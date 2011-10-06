#pragma once

#include <lambda_p/binder/node_binder.h>

#include <lambda_p_llvm/generation_context.h>

namespace llvm
{
    class Value;
}
namespace lambda_p_repl
{
	class hello_world_binder : public ::lambda_p::binder::node_binder
	{
	public:
		hello_world_binder (::llvm::Value * wprintf_a, ::lambda_p_llvm::generation_context context_a);
		~hello_world_binder (void);
		void bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
		::llvm::Value * wprintf;
        ::lambda_p_llvm::generation_context context;
	};
}

