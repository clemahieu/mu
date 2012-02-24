#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <vector>

namespace mu
{
	namespace core
	{
		class routine;
		class expression;
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
		class cluster;
		class routine
		{
		public:
			routine (boost::shared_ptr <mu::script::cluster::node> cluster_a, boost::shared_ptr <mu::core::routine> routine_a, boost::shared_ptr <mu::script::routine> result_a);
			std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
		};
	}
}

