#pragma once

#include <lambda_p/binder/binder.h>

namespace llvm
{
	class ExecutionEngine;
	class LLVMContext;
}
namespace lambda_p_llvm
{
	class overlay_binder : public lambda_p::binder::binder
	{
	public:
		overlay_binder (llvm::LLVMContext & context_a, llvm::ExecutionEngine * engine_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		llvm::LLVMContext & context;
		llvm::ExecutionEngine * engine;
	};
}

