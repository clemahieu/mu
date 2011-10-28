#pragma once

#include <lambda_p/binder/binder.h>

namespace llvm
{
	class Function;
}
namespace lambda_p_llvm
{
	class generation_context;
	class function_binder : public lambda_p::binder::binder
	{
	public:
		function_binder (lambda_p_llvm::generation_context & context_a, llvm::Function * function_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		lambda_p_llvm::generation_context & context;
		llvm::Function * function;
	};
}

