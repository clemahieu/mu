#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_llvm
{
	class generation_context;
	class generator : public lambda_p::binder::binder
	{
	public:
		generator (lambda_p_llvm::generation_context & context_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		lambda_p_llvm::generation_context & context;
	};
}

