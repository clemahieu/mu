#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p_llvm
{
	namespace basic_block
	{
		class node;
	}
	namespace context
	{
		class node;
	}
	namespace module
	{
		class node;
	}
	namespace analyzer
	{
		class context
		{
		public:
			boost::shared_ptr <lambda_p_llvm::context::node> context_m;
			boost::shared_ptr <lambda_p_llvm::module::node> module;
			boost::shared_ptr <lambda_p_llvm::basic_block::node> block;
		};
	}
}

