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
	class cluster;
	class routine;
}
namespace lambda_p_script_io
{
	class cluster
	{
	public:
		cluster (boost::shared_ptr <lambda_p::cluster> cluster_a);
		std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p_script::routine>> generated;
		boost::shared_ptr <lambda_p_script::cluster> result;
	};
}

