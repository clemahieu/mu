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
	class routine_instance;
	class call_inst_binder : public ::lambda_p::binder::binder
	{
	public:
		call_inst_binder (::lambda_p_llvm::generation_context & context_a);
		void bind (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
	private:
		::lambda_p_llvm::generation_context & context;
		void validate_argument_types (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
	};
}

