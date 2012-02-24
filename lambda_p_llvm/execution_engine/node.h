#pragma once

#include <mu/core/node.h>

namespace llvm
{
	class ExecutionEngine;
}
namespace lambda_p_llvm
{
	namespace execution_engine
	{
		class node : public mu::core::node
		{
		public:
			node (llvm::ExecutionEngine * engine_a);
			llvm::ExecutionEngine * engine;
		};
	}
}

