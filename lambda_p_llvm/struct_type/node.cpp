#include "node.h"

#include <lambda_p_llvm/context/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

lambda_p_llvm::struct_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> elements_a)
	: elements (elements_a),
	context (context_a)
{
}

llvm::Type * lambda_p_llvm::struct_type::node::type ()
{
	return struct_type ();
}

llvm::StructType * lambda_p_llvm::struct_type::node::struct_type ()
{
	std::vector <llvm::Type *> elements_l;
	for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i)
	{
		elements_l.push_back ((*i)->type ());
	}
	auto result (llvm::StructType::get (context->context, elements_l, false));
	return result;
}