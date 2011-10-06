#pragma once

#include <lambda_p/binder/node_instance.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace binder
	{
		class node_instance;
		class routine_instances : public ::lambda_p::binder::node_instance
		{
		public:
			routine_instances(void);
			::boost::shared_ptr < ::lambda_p::binder::node_instance> & operator [] (size_t node);
			::std::vector < ::boost::shared_ptr < ::lambda_p::binder::node_instance> > instances;
		};
	}
}

