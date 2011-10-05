#pragma once

#include <vector>
#include <map>

#include <llvm/DerivedTypes.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class node_instance;
	}
	namespace core
	{
		class node;
	}
	namespace errors
	{
		class error;
	}
}
namespace lambda_p_llvm
{
	class argument_binder
	{
	public:
		argument_binder(void);
		void apply (::std::vector < ::llvm::Value *> & arguments, ::std::vector < ::lambda_p::core::node *>::iterator argument, ::std::vector < ::lambda_p::core::node *>::iterator argument_end, ::llvm::FunctionType::param_iterator parameter, ::llvm::FunctionType::param_iterator parameter_end, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
	};
}

