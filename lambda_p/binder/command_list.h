#pragma once

#include <vector>

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
			void add_instance (::lambda_p::binder::node_instance * instance);
		private:
			::std::vector < ::lambda_p::binder::node_instance *> instances;
		};
	}
}

