#include "node.h"

#include <llvm/Module.h>

#include <sstream>

mu::llvm_::module::node::node (llvm::Module * module_a)
	: module (module_a)
{
}

std::wstring mu::llvm_::module::node::debug ()
{
	std::wstringstream result;
	result << L"mu::llvm_::module ";
	std::wstring module_name (module->getModuleIdentifier ().begin (), module->getModuleIdentifier ().end ());
	result << module_name;
	return result.str ();
}