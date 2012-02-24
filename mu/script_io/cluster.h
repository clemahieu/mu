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
	namespace script
	{
		class routine;
		namespace cluster
		{
			class node;
		}
	}
	namespace script_io
	{
		class cluster
		{
		public:
			cluster (boost::shared_ptr <mu::core::cluster> cluster_a);
			std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::script::routine>> generated;
			boost::shared_ptr <mu::script::cluster::node> result;
		};
	}
}

