#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	class cluster;
	class routine;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	class routine;
	class remapping;
	namespace cluster
	{
		class node;
	}
}
namespace lambda_p_script_io
{
	class cluster
	{
	public:
		cluster (boost::shared_ptr <lambda_p::cluster> cluster_a);
		boost::shared_ptr <lambda_p_script::remapping> remapping;
		boost::shared_ptr <lambda_p_script::cluster::node> result;
	};
}

