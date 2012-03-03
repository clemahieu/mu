#include <mu/llvm_/pointer_type.node.h>

#include <mu/llvm_/type.build.h>

#include <llvm/DerivedTypes.h>

mu::llvm_::pointer_type::node::node (boost::shared_ptr <mu::llvm_::context::node> context_a, llvm::PointerType * pointer_type_a)
{
	mu::llvm_::type::build build (context_a, pointer_type_a->getElementType ());
	element = build.type;
}

mu::llvm_::pointer_type::node::node (boost::shared_ptr <mu::llvm_::type::node> element_a)
	: element (element_a)
{
}

llvm::Type * mu::llvm_::pointer_type::node::type ()
{
	return pointer_type ();
}

llvm::PointerType * mu::llvm_::pointer_type::node::pointer_type ()
{
	auto result (llvm::PointerType::get (element->type (), 0));
	return result;
}
