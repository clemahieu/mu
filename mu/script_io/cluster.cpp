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
	: result (boost::make_shared <mu::script::cluster::node> ())
{
	std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::script::runtime::routine>> remapping;
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
	{
		process_routine (*i);
		auto existing (generated.find (*i));
		assert (existing != generated.end ());
		remapping [*i] = existing->second;
		result->routines.push_back (existing->second);
	}
	for (auto i (cluster_a->names.begin ()), j (cluster_a->names.end ()); i != j; ++i)
	{
		auto existing (remapping.find (i->second));
		assert (existing != remapping.end ());
		result->names [i->first] = existing->second;
	}
}

void mu::script_io::cluster::process_routine (boost::shared_ptr <mu::core::routine> routine_a)
{
	auto existing (generated.find (routine_a));
	if (existing == generated.end ())
	{
		auto result_l (boost::make_shared <mu::script::runtime::routine> (result));
		generated [routine_a] = result_l;
		mu::script_io::routine routine (*this, routine_a, result_l);
	}
}