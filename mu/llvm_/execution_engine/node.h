#pragma once

#include <mu/core/node.h>

namespace llvm
{
	class ExecutionEngine;
}
namespace mu
{
	namespace llvm_
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
}
