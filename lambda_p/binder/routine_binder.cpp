#include "routine_binder.h"

#include <lambda_p/binder/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/binder/routine.h>
#include <lambda_p/binder/bind_procedure.h>

#include <sstream>

lambda_p::binder::routine_binder::routine_binder(void)
{
}


void lambda_p::binder::routine_binder::bind (::lambda_p::core::statement * statement, routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < ::lambda_p::binder::routine> routine (::boost::dynamic_pointer_cast < ::lambda_p::binder::routine> (instances [statement->association->parameters [0]]));
		if (routine.get () != NULL)
		{
			::boost::shared_ptr < ::lambda_p::binder::routine_instances> instances_l (::boost::dynamic_pointer_cast < ::lambda_p::binder::routine_instances> (instances [statement->association->parameters [1]]));
			if (instances_l.get () != NULL)
			{
				core (*routine.get (), *instances_l.get (), problems);
			}
			else
			{
				unexpected_binder_type_error (1, ::std::wstring (L"routine_instances"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, ::std::wstring (L"routine"), problems);
		}
	}
}

void lambda_p::binder::routine_binder::core (::lambda_p::binder::routine & routine, ::lambda_p::binder::routine_instances & instances_l, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	size_t parameters (routine.routine_m->surface->results.size ());
	size_t binders (instances_l.instances.size ());
	if (parameters == binders)
	{
		size_t position (0);
		for (::std::vector < ::boost::shared_ptr < ::lambda_p::binder::instance> >::iterator i = instances_l.instances.begin (); i != instances_l.instances.end (); ++i, ++position)
		{
			if (i->get () != NULL)
			{
				routine.routine_m->instances [position] = *i;
			}
			else
			{
				::std::wstringstream message;
				message << L"argument for position: ";
				message << position;
				message << L" is not set";
				add_error (message.str (), problems);
			}
		}
		if (problems.empty ())
		{
			::lambda_p::binder::bind_procedure procedure (routine.routine_m);
			procedure (problems);
		}
	}
	else
	{
		::std::wstringstream message;
		message << L"number of parameters in routine surface: ";
		message << parameters;
		message << L" doesn't match number of arguments: ";
		message << binders;
		add_error (message.str (), problems);

	}
}

::std::wstring lambda_p::binder::routine_binder::binder_name ()
{
	return ::std::wstring (L"routine_binder");
}