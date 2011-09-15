#include "hello_world_binder.h"

#include <lambda_p_repl/hello_world.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/command_list.h>
#include <sstream>

lambda_p_repl::hello_world_binder::hello_world_binder (::boost::shared_ptr < ::lambda_p::binder::command_list> commands_a)
	: commands (commands_a)
{
}

lambda_p_repl::hello_world_binder::~hello_world_binder (void)
{
}

void lambda_p_repl::hello_world_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 1)
	{
		::boost::shared_ptr < ::lambda_p_repl::hello_world> hello (new ::lambda_p_repl::hello_world);
		commands->add_instance (hello);
	}
	else
	{
		problems << L"hello_world is expecting no arguments, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::hello_world_binder::operator () ()
{
}