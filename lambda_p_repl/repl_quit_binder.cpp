#include "repl_quit_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_repl/repl_quit.h>
#include <lambda_p/binder/bound_routine.h>

#include <string>
#include <sstream>

lambda_p_repl::repl_quit_binder::repl_quit_binder (::lambda_p_repl::repl & repl_a)
	: repl (repl_a)
{
}

lambda_p_repl::repl_quit_binder::~repl_quit_binder (void)
{
}

void lambda_p_repl::repl_quit_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 1)
	{
		::lambda_p_repl::repl_quit * quit = new ::lambda_p_repl::repl_quit (repl);
		routine.add_instance (quit);
	}
	else
	{
		problems << L"quit is expecting no arguments, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::repl_quit_binder::operator () ()
{
}