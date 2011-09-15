#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class node_instance;
		class command_list
		{
		public:
			command_list (void);
			~command_list (void);
			void operator () ();
			void add_instance (::boost::shared_ptr < ::lambda_p::binder::node_instance> instance);
		private:
			::std::vector < ::boost::shared_ptr < ::lambda_p::binder::node_instance> > instances;
		};
	}
}

