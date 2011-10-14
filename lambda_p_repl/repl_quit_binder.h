#pragma once

#include <lambda_p/binder/binder.h>

namespace llvm
{
    class Function;
    class Value;
}
namespace lambda_p_llvm
{
    class generation_context;
}
namespace lambda_p_repl
{
	class repl_quit;
	class repl_quit_binder : public ::lambda_p::binder::binder
	{
	public:
		repl_quit_binder (::lambda_p_llvm::generation_context & context_a, ::llvm::Function * quit_function_a, ::llvm::Value * quit_object_a);
		~repl_quit_binder (void);
		void bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
		::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit;
        ::lambda_p_llvm::generation_context & context;
        ::llvm::Function * quit_function;
        ::llvm::Value * quit_object;
	};
}

