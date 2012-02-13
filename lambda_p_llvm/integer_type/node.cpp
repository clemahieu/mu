#include "node.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::integer_type::node::node (llvm::IntegerType * type_a)
	: type_m (type_a)
{
}

llvm::Type * lambda_p_llvm::integer_type::node::type ()
{
	return integer_type ();
}

llvm::IntegerType * lambda_p_llvm::integer_type::node::integer_type ()
{
	return type_m;
}

std::wstring lambda_p_llvm::integer_type::node::name ()
{
	return std::wstring (L"lambda_p_llvm::integer_type::node");
}