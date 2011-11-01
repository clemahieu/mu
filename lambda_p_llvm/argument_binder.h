#pragma once

#include <vector>

#include <llvm/DerivedTypes.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class list;
		class node_list;
		class node;
	}
	namespace errors
	{
		class error;
		class error_list;
	}
}
namespace lambda_p_llvm
{
	class argument_binder
	{
	public:
		argument_binder(void);
		void apply (std::vector <llvm::Value *> & argument_values, boost::shared_ptr <lambda_p::binder::list> arguments, llvm::FunctionType::param_iterator parameter, llvm::FunctionType::param_iterator parameter_end, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems);
	};
}

