#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace mu
{
	namespace core
	{
		class cluster;
		class routine;
		namespace errors
		{
			class error_target;
		}
	}
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
	class cluster
	{
	public:
		cluster (boost::shared_ptr <mu::core::cluster> cluster_a);
		std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <lambda_p_script::routine>> generated;
		boost::shared_ptr <lambda_p_script::cluster::node> result;
	};
}

