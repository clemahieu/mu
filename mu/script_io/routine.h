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
		namespace runtime
		{
			class routine;
		}
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
			routine (mu::script_io::cluster & cluster_a, boost::shared_ptr <mu::core::routine> routine_a, boost::shared_ptr <mu::script::runtime::routine> result_a);
			std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
		};
	}
}

