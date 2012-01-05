#include "apply.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/errors/error_list.h>

#include <sstream>

lambda_p_kernel::apply::apply(void)
{
}


void lambda_p_kernel::apply::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::core::routine> routine (boost::dynamic_pointer_cast <lambda_p::core::routine> (nodes [statement->association->references [0]]));
		if (routine.get () != nullptr)
		{
			boost::shared_ptr <lambda_p::binder::list> nodes_l (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [1]]));
			if (nodes_l.get () != nullptr)
			{
				boost::shared_ptr <lambda_p::binder::list> actual_declarations (new lambda_p::binder::list);
				core (routine, *nodes_l.get (), problems, *actual_declarations);
				if (problems.errors.empty ())
				{
					nodes [statement->association->declarations [0]] = actual_declarations;
				}
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

void lambda_p_kernel::apply::core (boost::shared_ptr <lambda_p::core::routine> routine, lambda_p::binder::list & nodes_l, lambda_p::errors::error_list & problems, lambda_p::binder::list & declarations)
{
	size_t parameters (routine->surface->declarations.size ());
	size_t binders (nodes_l.nodes.size ());
	if (parameters == binders)
	{
		size_t position (0);
		lambda_p::binder::list actual_nodes;
		for (auto i = nodes_l.nodes.begin (); i != nodes_l.nodes.end (); ++i, ++position)
		{
			if (i->get () != nullptr)
			{
				actual_nodes [routine->surface->declarations [position]] = *i;
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
			lambda_p_kernel::bind_procedure procedure (routine, actual_nodes);
			procedure (problems);
			if (problems.errors.empty ())
			{
				size_t position (0);
				for (auto i = routine->surface->references.begin (); i != routine->surface->references.end (); ++i, ++position)
				{
					boost::shared_ptr <lambda_p::binder::node> node (actual_nodes [*i]);
					if (node.get () != nullptr)
					{
						declarations [position] = node;
					}
					else
					{
						std::wstringstream message;
						message << L"Routine did not set declaration at position: ";
						message << position;
						add_error (message.str (), problems);
					}
				}
				if (declarations.nodes.size () != routine->surface->references.size ())
				{
					std::wstringstream message;
					message << L"Routine did not set correct number of declarations, have: ";
					message << declarations.nodes.size ();
					message << L" need: ";
					message << routine->surface->references.size ();
					add_error (message.str (), problems);
				}
			}
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