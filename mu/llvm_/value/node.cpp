#include "node.h"

mu::llvm_::value::node::node (llvm::Value * value_a, mu::llvm_::type::node * type_a)
	: type (type_a),
	value_m (value_a)
{
}

llvm::Value * mu::llvm_::value::node::value ()
{
	return value_m;
}

std::wstring mu::llvm_::value::node::name ()
{
	return std::wstring (L"mu::llvm_::value::node");
}