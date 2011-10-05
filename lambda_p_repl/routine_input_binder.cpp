#include "routine_input_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_repl/routine_input.h>

#include <sstream>
#include <iostream>

lambda_p_repl::routine_input_binder::routine_input_binder(void)
{
}

lambda_p_repl::routine_input_binder::~routine_input_binder(void)
{
}

void lambda_p_repl::routine_input_binder::bind (::lambda_p::core::statement * statement, ::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	//size_t argument_count (statement->arguments.size ());
	//if (argument_count == 2)
	//{
	//	::lambda_p::core::node_id node_type (statement->arguments [1]->node_type ());
	//	switch (node_type)
	//	{
	//	case ::lambda_p::core::node_declaration:
	//		{
	//			::std::wcout << "Routine definition: ";
	//		}
	//		break;
	//	default:
	//		problems << "Routine input binder is expecting argument 1 to be a declaration, have: ";
	//		problems << statement->arguments [1]->node_type_name ();
	//		problems << '\n';
	//		break;
	//	}
	//}
	//else
	//{
	//	problems << "Routine input binder is expecting 1 argument, have: ";
	//	problems << argument_count;
	//	problems << '\n';
	//}
}