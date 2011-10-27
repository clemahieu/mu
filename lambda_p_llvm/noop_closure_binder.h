#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_llvm
{
	class generation_context;
	class noop_closure_binder : public lambda_p::binder::binder
	{
	public:
		noop_closure_binder (lambda_p_llvm::generation_context & context_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		lambda_p_llvm::generation_context & context;
	};
}

