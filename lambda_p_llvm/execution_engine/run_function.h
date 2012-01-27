#pragma once

#include <lambda_p_script/operation.h>
#include <lambda_p_llvm/execution_engine/node.h>

namespace llvm
{
	class Function;
}
namespace lambda_p_llvm
{
	namespace execution_engine
	{
		class node;
		class run_function : public lambda_p_script::operation
		{
		public:
			void perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			void perform_internal (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p_llvm::execution_engine::node> one, llvm::Function * function, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results);
			std::wstring name () override;
		};
	}
}

