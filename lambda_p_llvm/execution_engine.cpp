#include "execution_engine.h"

lambda_p_llvm::execution_engine::execution_engine (llvm::ExecutionEngine * engine_a)
	: engine (engine_a)
{
}