#include "apply.h"

#include <lambda_p_kernel/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_kernel/bind_procedure.h>

#include <sstream>

lambda_p_kernel::apply::apply(void)
{
}


void lambda_p_kernel::apply::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr < lambda_p_kernel::routine> routine (boost::dynamic_pointer_cast < lambda_p_kernel::routine> (instances [statement->association->parameters [0]]));
		if (routine.get () != NULL)
		{
			boost::shared_ptr < lambda_p::binder::routine_instances> instances_l (boost::dynamic_pointer_cast < lambda_p::binder::routine_instances> (instances [statement->association->parameters [1]]));
			if (instances_l.get () != NULL)
			{
				core (*routine.get (), *instances_l.get (), problems);
			}
			else
			{
				unexpected_binder_type_error (1, std::wstring (L"routine_instances"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"routine"), problems);
		}
	}
}

void lambda_p_kernel::apply::core (lambda_p_kernel::routine & routine, lambda_p::binder::routine_instances & instances_l, lambda_p::errors::error_list & problems)
{
	size_t parameters (routine.routine_m->surface->results.size ());
	size_t binders (instances_l.instances.size ());
	if (parameters == binders)
	{
		size_t position (0);
		for (std::vector < boost::shared_ptr < lambda_p::binder::instance> >::iterator i = instances_l.instances.begin (); i != instances_l.instances.end (); ++i, ++position)
		{
			if (i->get () != NULL)
			{
				routine.routine_m->instances [position] = *i;
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
			lambda_p_kernel::bind_procedure procedure (routine.routine_m);
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