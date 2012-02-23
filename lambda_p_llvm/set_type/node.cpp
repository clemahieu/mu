#include "node.h"

lambda_p_llvm::set_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a)
	: lambda_p_llvm::struct_type::node (context_a)
{
}

lambda_p_llvm::set_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> elements_a)
	: lambda_p_llvm::struct_type::node (context_a, elements_a)
{
}

lambda_p_llvm::set_type::node::node (boost::shared_ptr <lambda_p_llvm::struct_type::node> struct_a)
	 : lambda_p_llvm::struct_type::node (struct_a->context, struct_a->elements)
{
}