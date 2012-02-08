#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p_llvm
{
	namespace basic_block
	{
		class node;
		class instruction_insert : public lambda_p_script::fixed
		{
		public:
			instruction_insert (boost::shared_ptr <lambda_p_llvm::basic_block::node> block_a, boost::shared_ptr <lambda_p_script::fixed> instruction_a);
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
			boost::shared_ptr <lambda_p_llvm::basic_block::node> block;
			boost::shared_ptr <lambda_p_script::fixed> instruction;
		};
	}
}

