#include "add_global_variable.h"

#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/module/node.h>

#include <llvm/Module.h>

void mu::llvm_::module::add_global_variable::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::global_variable::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->module->getGlobalList ().push_back (two->global_variable ());
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::module::add_global_variable::count ()
{
	return 2;
}