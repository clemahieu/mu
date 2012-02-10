#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <vector>

namespace lambda_p
{
	class routine;
	class expression;
}
namespace lambda_p_script
{
	class routine;
	namespace cluster
	{
		class node;
	}
}
namespace lambda_p_script_io
{
	class cluster;
	class routine
	{
	public:
		routine (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_script::routine> result_a);
		std::map <boost::shared_ptr <lambda_p::expression>, size_t> reservations;
	};
}

