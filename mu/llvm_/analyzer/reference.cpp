#include "reference.h"

#include <mu/llvm_/function/node.h>

boost::shared_ptr <mu::core::node> mu::llvm_::analyzer::reference::operator () (boost::shared_ptr <mu::core::routine> routine_a)
{	
	auto existing_script (script_mapping.find (routine_a));
	assert (existing_script != script_mapping.end ());
	auto existing_function (function_mapping.find (existing_script->second));
	assert (existing_function != function_mapping.end ());
	return existing_function->second;
}