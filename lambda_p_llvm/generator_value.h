#pragma once

#include <lambda_p/binder/binder.h>

namespace llvm
{
	class Value;
	class BasicBlock;
}
namespace lambda_p_llvm
{
	class generator_value : public lambda_p::binder::binder
	{
	public:
		generator_value (llvm::Value * value_a, llvm::BasicBlock * block_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		llvm::Value * value;
		llvm::BasicBlock * block;
	};
}

