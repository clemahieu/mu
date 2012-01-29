#include "cluster.h"

#include <lambda_p/cluster.h>
#include <lambda_p/order.h>
#include <lambda_p/routine.h>
#include <lambda_p_script_io/routine.h>
#include <lambda_p_script/cluster.h>

#include <vector>

#include <boost/make_shared.hpp>

lambda_p_script_io::cluster::cluster (boost::shared_ptr <lambda_p::cluster> cluster_a)
{
	std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
	{
		auto value (*i);
		auto existing (generated.find (value));
		if (existing == generated.end ())
		{
			lambda_p_script_io::routine routine (generated, value);
			routines.push_back (routine.result);
			generated [value] = routine.result;
		}
		else
		{
			routines.push_back (existing->second);
		}
	}
	auto cluster (boost::make_shared <lambda_p_script::cluster> (cluster_a->names, routines));
	result = cluster;
}