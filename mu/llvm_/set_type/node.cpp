#include "node.h"

mu::llvm_::set_type::node::node (boost::shared_ptr <mu::llvm_::context::node> context_a)
	: mu::llvm_::struct_type::node (context_a)
{
}

mu::llvm_::set_type::node::node (boost::shared_ptr <mu::llvm_::context::node> context_a, std::vector <boost::shared_ptr <mu::llvm_::type::node>> elements_a)
	: mu::llvm_::struct_type::node (context_a, elements_a)
{
}

mu::llvm_::set_type::node::node (boost::shared_ptr <mu::llvm_::struct_type::node> struct_a)
	 : mu::llvm_::struct_type::node (struct_a->context, struct_a->elements)
{
}