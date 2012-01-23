#include "node.h"

lambda_p_llvm::function_pointer::node::node (llvm::Value * value_a, bool multiple_return_a)
	: lambda_p_llvm::value::node (value_a),
	multiple_return (multiple_return_a)
{
}