#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p_llvm
{
	class generation_context;
	class call_inst_binder : public ::lambda_p::binder::node_binder
	{
	public:
		call_inst_binder (::lambda_p_llvm::generation_context & context_a);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
	private:
		::lambda_p_llvm::generation_context & context;
		void validate_argument_types (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
	};
}

