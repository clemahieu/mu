#pragma once

#include <lambda_p_script/operation.h>

namespace lambda_p_llvm
{
	namespace basic_block
	{
		class node;
	}
	namespace ccall
	{
		class operation : public lambda_p_script::operation
		{
		public:
			operation (boost::shared_ptr <lambda_p_llvm::basic_block::node> block_a, boost::shared_ptr <lambda_p_script::operation> call_a);
			void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			boost::shared_ptr <lambda_p_llvm::basic_block::node> block;
			boost::shared_ptr <lambda_p_script::operation> call;
		};
	}
}

