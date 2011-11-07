#include "loop.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/bool_c.h>

#include <sstream>

void lambda_p_kernel::loop::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) 
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::routine> routine (boost::dynamic_pointer_cast <lambda_p_kernel::routine> (nodes [statement->association->references [0]]));
		check_binder (routine, 0, L"routine", problems);
		boost::shared_ptr <lambda_p::binder::list> list (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [1]]));
		check_binder (list, 1, L"list", problems);
		if (problems.errors.empty ())
		{		
			// Need one more reference than declaration for continue bool
			if (routine->routine_m->surface->declarations.size () + 1== routine->routine_m->surface->references.size ())
			{
				bool value (true);
				boost::shared_ptr <lambda_p::binder::list> declarations (new lambda_p::binder::list);
				declarations->merge (*list, problems);
				while (value && problems.errors.empty ())
				{
					lambda_p::binder::list references;
					references.merge (*declarations, problems);
					declarations->nodes.clear ();
					lambda_p_kernel::apply apply;
					apply.core (*routine, references, problems, *declarations);
					if (problems.errors.empty ())
					{
						size_t bool_index (routine->routine_m->surface->references.size () - 1);
						boost::shared_ptr <lambda_p_kernel::bool_c> condition (boost::dynamic_pointer_cast <lambda_p_kernel::bool_c> (declarations->operator[] (bool_index)));
						check_binder (condition, 0, L"bool_c", problems);
						if (problems.errors.empty ())
						{
							value = condition->value;
							declarations->nodes.resize (bool_index);
						}
					}
				}
				nodes [statement->association->declarations [0]] = declarations;
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

std::wstring lambda_p_kernel::loop::binder_name ()
{
	return std::wstring (L"loop");
}