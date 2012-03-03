#include <mu/llvm_/argument.node.h>

#include <llvm/Argument.h>

mu::llvm_::argument::node::node (llvm::Argument * argument_a, boost::shared_ptr <mu::llvm_::type::node> type_a)
	: mu::llvm_::value::node (argument_a, type_a)
{
}

llvm::Argument * mu::llvm_::argument::node::argument ()
{
	auto result (llvm::cast <llvm::Argument> (value_m));
	return result;
}
