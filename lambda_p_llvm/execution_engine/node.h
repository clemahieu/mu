#pragma once

#include <lambda_p/node.h>

namespace llvm
{
	class ExecutionEngine;
}
namespace lambda_p_llvm
{
	namespace execution_engine
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::ExecutionEngine * engine_a);
			llvm::ExecutionEngine * engine;
		};
	}
}

