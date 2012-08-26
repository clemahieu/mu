#include <mu/llvm_/array_type_node.h>

#include <mu/llvm_/type_build.h>

#include <llvm/DerivedTypes.h>

mu::llvm_::array_type::node::node (mu::llvm_::context::node * context_a, llvm::ArrayType * array_type_a):
count (array_type_a->getNumElements ())
{
	mu::llvm_::type::build build (context_a, array_type_a->getElementType ());
	element = build.type;
}

mu::llvm_::array_type::node::node (mu::llvm_::type::node * element_a, size_t count_a):
element (element_a),
count (count_a)
{
}

llvm::Type * mu::llvm_::array_type::node::type ()
{
	return array_type ();
}

llvm::ArrayType * mu::llvm_::array_type::node::array_type ()
{
	auto result (llvm::ArrayType::get (element->type (), count));
	return result;
}