#include <mu/llvm_/cluster/remap.h>

#include <mu/llvm_/function/node.h>
#include <mu/core/routine.h>

mu::core::node * mu::llvm_::cluster::remap::operator () (mu::core::node * node_a)
{
	auto result (node_a);
	auto routine (dynamic_cast <mu::core::routine *> (node_a));
	if (routine != nullptr)
	{
		auto existing (mapping.find (routine));
		if (existing != mapping.end ())
		{
			result = existing->second;
		}
	}
	return result;
}