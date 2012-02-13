#include "node.h"

#include <lambda_p/routine.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_script/cluster/node.h>

void lambda_p_llvm::cluster::node::set_names (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> & remap_a)
{
	for (auto i (cluster_a->names.begin ()), j (cluster_a->names.end ()); i != j; ++i)
	{
		auto existing (remap_a.find (cluster_a->mapping [i->second]));
		if (existing != remap_a.end ())
		{
			auto value (boost::static_pointer_cast <lambda_p_llvm::value::node> (existing->second));
			names [i->first] = value;
		}
	}
}