#pragma once

#include <lambda_p/binder/binder.h>

namespace llvm
{
	class ExecutionEngine;
	class LLVMContext;
	class Type;
}
namespace lambda_p_llvm
{
	class overlay_binder : public lambda_p::binder::binder
	{
	public:
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
	};
}

