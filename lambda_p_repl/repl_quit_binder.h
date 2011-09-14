#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p_repl
{
	class repl;
	class repl_quit_binder : public ::lambda_p::binder::node_binder
	{
	public:
		repl_quit_binder (::boost::shared_ptr < ::lambda_p::binder::bound_routine> routine_a, ::lambda_p_repl::repl & repl_a);
		~repl_quit_binder (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
		void operator () ();
		::lambda_p_repl::repl & repl;
		::boost::shared_ptr < ::lambda_p::binder::bound_routine> routine;
	};
}

