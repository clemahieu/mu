#include "echo_binder.h"


#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_repl/echo.h>
#include <lambda_p/core/data.h>
#include <lambda_p/binder/bound_routine.h>

#include <sstream>

lambda_p_repl::echo_binder::echo_binder(void)
{
}

lambda_p_repl::echo_binder::~echo_binder(void)
{
}

void lambda_p_repl::echo_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 2)
	{
		::lambda_p::core::node_id node_id (statement->arguments [1]->node_type ());
		switch (node_id)
		{
		case ::lambda_p::core::node_data:
			{
				::lambda_p::core::data * data (static_cast < ::lambda_p::core::data *> (statement->arguments [1]));
				::lambda_p_repl::echo * echo (new ::lambda_p_repl::echo (data->string ()));
				routine.add_instance (echo);
			}
			break;
		default:
			problems << L"echo is expecting argument 1 to be data, have: ";
			problems << statement->arguments [1]->node_type_name ();
			problems << '\n';
			break;
		}
	}
	else
	{
		problems << L"echo is expecting one argument, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::echo_binder::operator () ()
{
}