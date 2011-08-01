#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <vector>

#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace core
	{
		class statement
		{
		public:
			statement (::std::string name_a, ::boost::shared_ptr < ::lambda_p::core::node> target_a);
			~statement (void);
			::boost::shared_ptr < ::lambda_p::core::node> name;
			::boost::shared_ptr < ::lambda_p::core::node> target;
			::std::vector < ::boost::shared_ptr < ::lambda_p::core::node> > connections;
		};
	}
}
