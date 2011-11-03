#pragma once

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class LLVMContext;
	class ExecutionEngine;
}
namespace lambda_p_kernel
{
	class package;
}
namespace lambda_p_llvm
{
	class generation_context;
	class wprintf_function;
	class malloc_function;
	class abort_function;
	class memcpy_function;
}
namespace lambda_p_repl
{
	class api
	{
	public:
		api (llvm::ExecutionEngine * engine_a, lambda_p_llvm::generation_context & context, lambda_p_llvm::wprintf_function & wprintf, lambda_p_llvm::malloc_function & malloc, lambda_p_llvm::abort_function & abort, lambda_p_llvm::memcpy_function & memcpy);
		boost::shared_ptr <lambda_p_kernel::package> package;
	};
}

