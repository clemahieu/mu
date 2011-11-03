#pragma once

#include <lambda_p/binder/node.h>

namespace llvm
{
	class ExecutionEngine;
}
namespace lambda_p_llvm
{
	class execution_engine : public lambda_p::binder::node
	{
	public:
		execution_engine (llvm::ExecutionEngine * engine_a);
		llvm::ExecutionEngine * engine;
	};
}

