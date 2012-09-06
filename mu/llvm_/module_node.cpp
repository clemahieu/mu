#include <mu/llvm_/module_node.h>

#include <llvm/Module.h>

#include <sstream>

mu::llvm_::module::node::node (llvm::Module * module_a)
	: module (module_a)
{
}

mu::string mu::llvm_::module::node::debug ()
{
	mu::stringstream result;
	result << U"mu::llvm_::module ";
	mu::string module_name (module->getModuleIdentifier ().begin (), module->getModuleIdentifier ().end ());
	result << module_name;
	return result.str ();
}