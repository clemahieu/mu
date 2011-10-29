#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p_kernel
{
	class package;
}
namespace lambda_p_llvm
{
    class generation_context;
	class malloc_function;
	class memcpy_function;
	class api
	{
	public:
		api (lambda_p_llvm::generation_context & context, lambda_p_llvm::malloc_function & malloc, lambda_p_llvm::memcpy_function & memcpy);
		boost::shared_ptr <lambda_p_kernel::package> package;
	};
}

