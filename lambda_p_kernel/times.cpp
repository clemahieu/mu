#include "times.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_kernel/number.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/core/routine.h>

#include <sstream>

void lambda_p_kernel::times::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 3, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::routine> routine (boost::dynamic_pointer_cast <lambda_p_kernel::routine> (nodes [statement->association->references [0]]));
		check_binder (routine, 0, L"routine", problems);
		boost::shared_ptr <lambda_p::binder::list> nodes_l (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [1]]));
		check_binder (nodes_l, 1, L"list", problems);
		boost::shared_ptr <lambda_p_kernel::number> number (boost::dynamic_pointer_cast <lambda_p_kernel::number> (nodes [statement->association->references [2]]));
		check_binder (number, 2, L"number", problems);
		if (problems.errors.empty ())
		{
			if (routine->routine_m->surface->declarations.size () == routine->routine_m->surface->references.size ())
			{
				boost::shared_ptr <lambda_p::binder::list> declarations (new lambda_p::binder::list);
				declarations->merge (*nodes_l, problems);
				if (problems.errors.empty ())
				{
					for (size_t i (0); i < number->value && problems.errors.empty (); ++i)
					{
						lambda_p::binder::list references (*declarations);
						declarations->nodes.clear ();
						lambda_p_kernel::apply apply;
						apply.core (routine, references, problems, *declarations);
					}
					if (problems.errors.empty ())
					{
						nodes [statement->association->declarations [0]] = declarations;
					}
				}
			}
			else
			{
				std::wstringstream message;
				message << L"Number of declarations in routine's surface: ";
				message << routine->routine_m->surface->declarations.size ();
				message << L" does not match number of references: ";
				message << routine->routine_m->surface->references.size ();
				add_error (message.str (), problems);
			}
		}
	}
}

std::wstring lambda_p_kernel::times::binder_name ()
{
	return std::wstring (L"times");
}