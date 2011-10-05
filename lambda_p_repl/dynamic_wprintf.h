#pragma once

#include <lambda_p/binder/node_binder.h>

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
	class dynamic_wprintf : public ::lambda_p::binder::node_binder
	{
	public:
		dynamic_wprintf (::llvm::Value * wprintf_a, ::lambda_p_llvm::generation_context & context_a);
		~dynamic_wprintf (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
	private:
		void problem (size_t argument_position, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::lambda_p_llvm::generation_context & context;
		::llvm::Value * wprintf;
	};
}

