#include "node.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::pointer_type::node::node (boost::shared_ptr <lambda_p_llvm::type::node> element_a)
	: element (element_a)
{
}

llvm::Type * lambda_p_llvm::pointer_type::node::type ()
{
	return pointer_type ();
}

llvm::PointerType * lambda_p_llvm::pointer_type::node::pointer_type ()
{
	auto result (llvm::PointerType::get (element->type (), 0));
	return result;
}