#pragma once

namespace llvm
{
	class Function;
}
namespace lambda_p_llvm
{
	class generation_context;
	class abort_function
	{
	public:
		abort_function (lambda_p_llvm::generation_context & context_a);
		llvm::Function * abort;
	};
}

