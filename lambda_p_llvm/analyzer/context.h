#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p_llvm
{
	namespace basic_block
	{
		class node;
	}
	namespace analyzer
	{
		class context
		{
		public:
			boost::shared_ptr <lambda_p_llvm::basic_block::node> block;
		};
	}
}

