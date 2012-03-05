#include "reference.h"

#include <mu/llvm_/function/node.h>

boost::shared_ptr <mu::core::node> mu::llvm_::analyzer::reference::operator () (boost::shared_ptr <mu::core::routine> routine_a)
{	
	auto existing (mapping.find (routine_a));
	assert (existing != mapping.end ());
	return existing->second;
}