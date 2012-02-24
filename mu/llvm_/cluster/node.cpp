#include "node.h"

#include <mu/core/routine.h>
#include <mu/llvm_/function/node.h>
#include <mu/script/cluster/node.h>

void mu::llvm_::cluster::node::set_names (boost::shared_ptr <mu::script::cluster::node> cluster_a, std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> & remap_a)
{
	for (auto i (cluster_a->names.begin ()), j (cluster_a->names.end ()); i != j; ++i)
	{
		auto existing (remap_a.find (cluster_a->mapping [i->second]));
		if (existing != remap_a.end ())
		{
			auto value (boost::static_pointer_cast <mu::llvm_::function::node> (existing->second));
			names [i->first] = value;
		}
	}
}

std::wstring mu::llvm_::cluster::node::name ()
{
	return std::wstring (L"mu::llvm_::cluster::node");
}