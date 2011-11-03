#include "apply.h"

#include <lambda_p_kernel/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/errors/error_list.h>

#include <sstream>

lambda_p_kernel::apply::apply(void)
{
}


void lambda_p_kernel::apply::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::routine> routine (boost::dynamic_pointer_cast <lambda_p_kernel::routine> (nodes [statement->association->references [0]]));
		if (routine.get () != nullptr)
		{
			boost::shared_ptr <lambda_p::binder::node_list> nodes_l (boost::dynamic_pointer_cast <lambda_p::binder::node_list> (nodes [statement->association->references [1]]));
			if (nodes_l.get () != nullptr)
			{
				core (*routine.get (), *nodes_l.get (), problems);
			}
			else
			{
				unexpected_binder_type_error (1, L"routine_nodes", problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, L"routine", problems);
		}
	}
}

void lambda_p_kernel::apply::core (lambda_p_kernel::routine & routine, lambda_p::binder::node_list & nodes_l, lambda_p::errors::error_list & problems)
{
	size_t parameters (routine.routine_m->surface->declarations.size ());
	size_t binders (nodes_l.nodes.size ());
	if (parameters == binders)
	{
		size_t position (0);
		for (auto i = nodes_l.nodes.begin (); i != nodes_l.nodes.end (); ++i, ++position)
		{
			if (i->get () != nullptr)
			{
				actual_nodes [routine.routine_m->surface->declarations [position]] = *i;
			}
			else
			{
				std::wstringstream message;
				message << L"argument for position: ";
				message << position;
				message << L" is not set";
				add_error (message.str (), problems);
			}
		}
		if (problems.errors.empty ())
		{
			lambda_p_kernel::bind_procedure procedure (routine.routine_m, actual_nodes);
			procedure (problems);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"number of parameters in routine surface: ";
		message << parameters;
		message << L" doesn't match number of arguments: ";
		message << binders;
		add_error (message.str (), problems);

	}
}

std::wstring lambda_p_kernel::apply::binder_name ()
{
	return std::wstring (L"apply");
}