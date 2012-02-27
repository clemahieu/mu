#include "cluster.h"

#include <mu/core/cluster.h>
#include <mu/core/order.h>
#include <mu/core/routine.h>
#include <mu/script_io/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>

#include <vector>

#include <boost/make_shared.hpp>

mu::script_io::cluster::cluster (boost::shared_ptr <mu::core::cluster> cluster_a)
{
	auto cluster (boost::make_shared <mu::script::cluster::node> ());
	cluster->names = cluster_a->names;
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
	{
		auto value (*i);
		auto existing (generated.find (value));
		if (existing == generated.end ())
		{
			auto result_l (boost::make_shared <mu::script::routine> (cluster));
			cluster->mapping [value] = result_l;
			generated [value] = result_l;
			mu::script_io::routine routine (cluster, value, result_l);
			cluster->routines.push_back (result_l);
		}
		else
		{
			cluster->routines.push_back (existing->second);
		}
	}
	result = cluster;
}