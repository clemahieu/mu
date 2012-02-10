#pragma once

#include <lambda_p/segment.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	namespace cluster
	{
		class node;
	}
	class context
	{
	public:
		context (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, boost::shared_ptr <lambda_p::node> parameters_a, size_t size);
		boost::shared_ptr <lambda_p::node> parameters;
		boost::shared_ptr <lambda_p_script::cluster::node> cluster;
		std::vector <std::vector <boost::shared_ptr <lambda_p::node>>> nodes;
	};
}

