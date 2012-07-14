#include <mu/llvm_/global_value/set_linkage.h>

#include <mu/llvm_/global_value/node.h>
#include <mu/llvm_/linkage_types/node.h>
#include <mu/script/check.h>

bool mu::llvm_::global_value::set_linkage::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::global_value::node, mu::llvm_::linkage_types::node> () (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::global_value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::linkage_types::node *> (context_a.parameters (1)));
		one->global_value ()->setLinkage (two->type);
	}
	return valid;
}