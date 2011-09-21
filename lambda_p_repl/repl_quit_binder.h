#pragma once

#include <lambda_p/binder/node_binder.h>

namespace llvm
{
    class Function;
    class Value;
}
namespace lambda_p
{
	namespace binder
	{
		class command_list;
	}
}
namespace lambda_p_llvm
{
    class generation_context;
}
namespace lambda_p_repl
{
	class repl_quit;
	class repl_quit_binder : public ::lambda_p::binder::node_binder
	{
	public:
		repl_quit_binder (::lambda_p_llvm::generation_context & context_a, ::llvm::Function * quit_function_a, ::llvm::Value * quit_object_a);
		~repl_quit_binder (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
		void operator () ();
		::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit;
        ::lambda_p_llvm::generation_context & context;
        ::llvm::Function * quit_function;
        ::llvm::Value * quit_object;
	};
}

