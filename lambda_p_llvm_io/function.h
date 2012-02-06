#pragma once

#include <lambda_p_llvm_io/target.h>

namespace lambda_p_llvm
{
	namespace function_pointer
	{
		class node;
	}
}
namespace lambda_p_llvm_io
{
	class expression;
	namespace value
	{
		class node;
	}
	class function : public lambda_p_llvm_io::target
	{
	public:
		function (lambda_p_llvm_io::expression & expression_a, boost::shared_ptr <lambda_p_llvm::function_pointer::node> function_a);
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		boost::shared_ptr <lambda_p_llvm::function_pointer::node> function_m;
		lambda_p_llvm_io::expression & expression;
	};
}

