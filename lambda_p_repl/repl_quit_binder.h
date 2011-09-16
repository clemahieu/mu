#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
	namespace binder
	{
		class command_list;
	}
}
namespace lambda_p_repl
{
	class repl_quit;
	class repl_quit_binder : public ::lambda_p::binder::node_binder
	{
	public:
		repl_quit_binder (::boost::shared_ptr < ::lambda_p::binder::command_list> routine_a, ::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit_a);
		~repl_quit_binder (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
		void operator () ();
		::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit;
		::boost::shared_ptr < ::lambda_p::binder::command_list> commands;
	};
}

