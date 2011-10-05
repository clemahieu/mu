#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p_llvm
{
	class generation_context;
	class alloca_inst_binder : public ::lambda_p::binder::node_binder
	{
	public:
		alloca_inst_binder (::lambda_p_llvm::generation_context & context_a);
		void bind (::lambda_p::core::statement * statement, ::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
		::lambda_p_llvm::generation_context & context;
	};
}

