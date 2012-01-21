#include "node.h"

#include <sstream>

lambda_p_llvm_wrapper::execution_engine::generic_value::node::node (llvm::GenericValue & value_a)
	: value (value_a)
{
}

std::wstring lambda_p_llvm_wrapper::execution_engine::generic_value::node::debug ()
{
	auto string (value.IntVal.toString (16, false));
	std::wstring value (string.begin (), string.end ());
	return value;
}