#pragma once

#include <lambda_p/binder/node_instance.h>

#include <boost/shared_ptr.hpp>

#include <iostream>
#include <map>

namespace lambda_p
{
	namespace core
	{
		class statement;
		class node;
	}
	namespace binder
	{
		class bound_routine;
		class node_binder : public node_instance
		{
		public:
			node_binder(void);
			~node_binder(void);
			virtual void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems) = 0;
		};
	}
}

