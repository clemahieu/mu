#include "cluster.h"

#include <lambda_p/cluster.h>
#include <lambda_p/order.h>
#include <lambda_p/routine.h>
#include <lambda_p_script_io/routine.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/remapping.h>

#include <vector>

#include <boost/make_shared.hpp>

lambda_p_script_io::cluster::cluster (boost::shared_ptr <lambda_p::cluster> cluster_a)
	: remapping (new lambda_p_script::remapping)
{
	std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
	{
		auto value (*i);
		auto existing (remapping->generated.find (value));
		if (existing == remapping->generated.end ())
		{
			auto result_l (boost::make_shared <lambda_p_script::routine> ());
			remapping->generated [value] = result_l;
			lambda_p_script_io::routine routine (remapping, value, result_l);
			routines.push_back (result_l);
		}
		else
		{
			routines.push_back (existing->second);
		}
	}
	auto cluster (boost::make_shared <lambda_p_script::cluster::node> (cluster_a->names, routines, remapping));
	result = cluster;
}