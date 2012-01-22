#pragma once

#include <lambda_p/node.h>

namespace llvm
{
	class BasicBlock;
}
namespace lambda_p_llvm
{
	namespace basic_block
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::BasicBlock * block_a);
			llvm::BasicBlock * block;
		};
	}
}

