#pragma once

#include <lambda_p_llvm/type/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class FunctionType;
}
namespace lambda_p_llvm
{
	namespace context
	{
		class node;
	}
	namespace function_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, llvm::FunctionType * function_type_a);
			node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> parameters_a, boost::shared_ptr <lambda_p_llvm::type::node> output_a);
			llvm::Type * type () override;
			llvm::FunctionType * function_type ();
			boost::shared_ptr <lambda_p_llvm::context::node> context;
			std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> parameters;
			boost::shared_ptr <lambda_p_llvm::type::node> output;
		};
	}
}

