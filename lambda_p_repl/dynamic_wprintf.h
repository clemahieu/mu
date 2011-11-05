#pragma once

#include <lambda_p/binder/binder.h>

namespace llvm
{
	class Value;
}
namespace lambda_p_llvm
{
	class generation_context;
}
namespace lambda_p_repl
{
	class dynamic_wprintf : public lambda_p::binder::binder
	{
	public:
		dynamic_wprintf (llvm::Value * wprintf_a, lambda_p_llvm::generation_context & context_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name ();
	private:
		void problem (size_t argument_position, lambda_p::errors::error_list & problems);
		lambda_p_llvm::generation_context & context;
		llvm::Value * wprintf;
	};
}

