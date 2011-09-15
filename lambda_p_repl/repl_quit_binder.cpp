#include "repl_quit_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_repl/repl_quit.h>
#include <lambda_p/binder/command_list.h>

#include <string>
#include <sstream>

lambda_p_repl::repl_quit_binder::repl_quit_binder (::boost::shared_ptr < ::lambda_p::binder::command_list> commands_a, ::lambda_p_repl::repl & repl_a)
	: commands (commands_a),
	repl (repl_a)
{
}

lambda_p_repl::repl_quit_binder::~repl_quit_binder (void)
{
}

void lambda_p_repl::repl_quit_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 1)
	{
		::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit (new ::lambda_p_repl::repl_quit (repl));
		commands->add_instance (quit);
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