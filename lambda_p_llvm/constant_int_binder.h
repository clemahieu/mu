#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
	namespace core
	{
		class node;
	}
}
namespace lambda_p_llvm
{
	class generation_context;
	class constant_int_binder : public ::lambda_p::binder::node_binder
	{
	public:
		constant_int_binder (::lambda_p_llvm::generation_context & context_a);
		~constant_int_binder (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
	private:
		void parse_number (unsigned long base, ::std::wstring & number_wstring, ::lambda_p::core::node * declaration_node, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
		void parse_nodes (::lambda_p::core::node * base_node, ::lambda_p::core::node * number_node, ::lambda_p::core::node * declaration_node, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
		::lambda_p_llvm::generation_context & context;
	};
}

