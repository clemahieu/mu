#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p_repl
{
	class hello_world_binder : public ::lambda_p::binder::node_binder
	{
	public:
		hello_world_binder (::boost::shared_ptr < ::lambda_p::binder::bound_routine> routine_a);
		~hello_world_binder (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
		void operator () ();
		::boost::shared_ptr < ::lambda_p::binder::bound_routine> routine;
	};
}

