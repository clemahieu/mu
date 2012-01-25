#include "node.h"

#include <llvm/Module.h>

#include <sstream>

lambda_p_llvm::module::node::node (llvm::Module * module_a)
	: module (module_a)
{
}

std::wstring lambda_p_llvm::module::node::debug ()
{
	std::wstringstream result;
	result << L"lambda_p_llvm::module ";
	std::wstring module_name (module->getModuleIdentifier ().begin (), module->getModuleIdentifier ().end ());
	result << module_name;
	return result.str ();
}