#pragma once

#include <lambda_p_script/operation.h>

namespace lambda_p_llvm
{
	namespace basic_block
	{
		class node;
		class split_return : public lambda_p_script::operation
		{
		public:
			split_return (boost::shared_ptr <lambda_p_llvm::basic_block::node> block_a, boost::shared_ptr <lambda_p_script::operation> next_a);
			void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			boost::shared_ptr <lambda_p_script::operation> next;
			boost::shared_ptr <lambda_p_llvm::basic_block::node> block;
		};
	}
}

