#include <mu/script/cluster/remap_node.h>

boost::shared_ptr <mu::core::node> mu::script::cluster::remap_node::operator () (boost::shared_ptr <mu::core::node> node_a)
{
	boost::shared_ptr <mu::core::node> result;
	auto existing (mapping.find (node_a));
	if (existing != mapping.end ())
	{
		result = existing->second;
	}
	return result;
}