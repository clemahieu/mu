#pragma once

#include <lambda_p/binder/binder.h>
#include <lambda_p_llvm/generation_context.h>

namespace llvm
{
    class GlobalVariable;
    class Value;
}
namespace lambda_p_llvm
{
    class generation_context;
}
namespace lambda_p_repl
{
	class echo_binder : public lambda_p::binder::binder
	{
	public:
		echo_binder (llvm::Value * wprintf_a, lambda_p_llvm::generation_context context_a);
		~echo_binder (void);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
		std::wstring binder_name ();
		lambda_p_llvm::generation_context context;
        llvm::Value * echo_string_global;
        llvm::Value * wprintf;
	};
}
