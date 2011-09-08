#pragma once

#include <lambda_p/binder/node_instance.h>

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
			virtual void bind (::lambda_p::core::statement *, ::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_instance *> & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstring & problems) = 0;
		};
	}
}

