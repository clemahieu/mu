#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
	namespace binder
	{
		class command_list;
	}
}
namespace lambda_p_llvm
{
	class llvm_context_new : public ::lambda_p::binder::node_binder
	{
	public:
		llvm_context_new (::boost::shared_ptr < ::lambda_p::binder::command_list> commands_a);
		~llvm_context_new (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
		::boost::shared_ptr < ::lambda_p::binder::command_list> commands;
	};
}

