#include "set_linkage.h"

#include <mu/llvm_/global_value/node.h>
#include <mu/llvm_/linkage_types/node.h>
#include <mu/script/check.h>

void mu::llvm_::global_value::set_linkage::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::global_value::node, mu::llvm_::linkage_types::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::global_value::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::linkage_types::node> (context_a.parameters [1]));
		one->global_value ()->setLinkage (two->type);
	}
}