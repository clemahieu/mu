#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p_repl
{
	class repl;
	class repl_quit_binder : public ::lambda_p::binder::node_binder
	{
	public:
		repl_quit_binder (::lambda_p_repl::repl & repl_a);
		~repl_quit_binder (void);
		void bind (::lambda_p::core::statement *, ::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_instance *> & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems);
		::lambda_p_repl::repl & repl;
	};
}

