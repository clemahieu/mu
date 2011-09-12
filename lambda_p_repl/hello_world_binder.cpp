#include "hello_world_binder.h"

#include <lambda_p_repl/hello_world.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/bound_routine.h>
#include <sstream>

lambda_p_repl::hello_world_binder::hello_world_binder(void)
{
}

lambda_p_repl::hello_world_binder::~hello_world_binder(void)
{
}

void lambda_p_repl::hello_world_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 1)
	{
		::lambda_p_repl::hello_world * hello (new ::lambda_p_repl::hello_world);
		routine.add_instance (hello);
	}
	else
	{
		problems << L"quit is expecting no arguments, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::hello_world_binder::operator () ()
{
}