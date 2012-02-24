#include "node.h"

#include <sstream>

mu::llvm_::execution_engine::generic_value::node::node ()
{
}

mu::llvm_::execution_engine::generic_value::node::node (llvm::GenericValue & value_a)
	: value (value_a)
{
}

std::wstring mu::llvm_::execution_engine::generic_value::node::debug ()
{
	auto string (value.IntVal.toString (16, false));
	std::wstring value (string.begin (), string.end ());
	return value;
}