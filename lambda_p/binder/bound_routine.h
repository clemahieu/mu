#pragma once

#include <vector>

namespace lambda_p
{
	namespace binder
	{
		class node_instance;
		class bound_routine
		{
		public:
			bound_routine (void);
			~bound_routine (void);
			void operator () ();
			void add_instance (::lambda_p::binder::node_instance * instance);
		private:
			::std::vector < ::lambda_p::binder::node_instance *> instances;
		};
	}
}

