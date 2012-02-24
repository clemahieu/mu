#pragma once

#include <mu/core/node.h>

namespace llvm
{
	class BasicBlock;
}
namespace lambda_p_llvm
{
	namespace basic_block
	{
		class node : public mu::core::node
		{
		public:
			node (llvm::BasicBlock * block_a);
			llvm::BasicBlock * block;
		};
	}
}

