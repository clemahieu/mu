#include "set_linkage.h"

#include <mu/llvm_/global_value/node.h>
#include <mu/llvm_/linkage_types/node.h>

void mu::llvm_::global_value::set_linkage::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::global_value::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::linkage_types::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->global_value ()->setLinkage (two->type);
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

size_t mu::llvm_::global_value::set_linkage::count ()
{
	return 2;
}