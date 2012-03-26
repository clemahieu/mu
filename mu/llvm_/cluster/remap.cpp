#include <mu/llvm_/cluster/remap.h>

#include <mu/llvm_/function/node.h>
#include <mu/core/routine.h>

boost::shared_ptr <mu::core::node> mu::llvm_::cluster::remap::operator () (boost::shared_ptr <mu::core::node> node_a)
{
	boost::shared_ptr <mu::core::node> result (node_a);
	auto routine (boost::dynamic_pointer_cast <mu::core::routine> (node_a));
	if (routine.get () != nullptr)
	{
		auto existing (mapping.find (routine));
		if (existing != mapping.end ())
		{
			result = existing->second;
		}
	}
	return result;
}