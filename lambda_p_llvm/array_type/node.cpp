#include "node.h"

#include <lambda_p_llvm/type/build.h>

#include <llvm/DerivedTypes.h>

lambda_p_llvm::array_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, llvm::ArrayType * array_type_a)
	: count (array_type_a->getNumElements ())
{
	lambda_p_llvm::type::build build (context_a, array_type_a->getElementType ());
	element = build.type;
}

lambda_p_llvm::array_type::node::node (boost::shared_ptr <lambda_p_llvm::type::node> element_a, size_t count_a)
	: element (element_a),
	count (count_a)
{
}

llvm::Type * lambda_p_llvm::array_type::node::type ()
{
	return array_type ();
}

llvm::ArrayType * lambda_p_llvm::array_type::node::array_type ()
{
	auto result (llvm::ArrayType::get (element->type (), count));
	return result;
}