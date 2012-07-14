#include <mu/script/cluster/remap_node.h>

mu::core::node * mu::script::cluster::remap_node::operator () (mu::core::node * node_a)
{
	auto result (node_a);
	auto existing (mapping.find (node_a));
	if (existing != mapping.end ())
	{
		result = existing->second;
	}
	return result;
}