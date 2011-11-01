#pragma once

#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/memcpy_function.h>
#include <lambda_p_llvm/abort_function.h>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class Module;
	class ExecutionEngine;
}
namespace lambda_p_llvm
{
	class generation_context;
}
namespace lambda_p_repl
{
	class overlayed_functions
	{
	public:
		overlayed_functions (llvm::Module * module, boost::shared_ptr <lambda_p_llvm::generation_context> context, llvm::ExecutionEngine * engine);
		lambda_p_llvm::wprintf_function wprintf;
		lambda_p_llvm::malloc_function malloc;
		lambda_p_llvm::memcpy_function memcpy;
		lambda_p_llvm::abort_function abort;
	};
}

