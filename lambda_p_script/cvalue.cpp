#include "cvalue.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/bool_c.h>
#include <lambda_p_kernel/application.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/core/routine.h>

void lambda_p_kernel::cvalue::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 3, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::bool_c> bool_l (boost::dynamic_pointer_cast <lambda_p_kernel::bool_c> (nodes [statement->association->references [0]]));
		check_binder (bool_l, 0, L"bool_c", problems);
		if (problems.errors.empty ())
		{
			if (bool_l->value)
			{
				boost::shared_ptr <lambda_p::binder::node> node (nodes [statement->association->references [1]]);
				nodes [statement->association->declarations [0]] = node;
			}
			else
			{
				boost::shared_ptr <lambda_p::binder::node> node (nodes [statement->association->references [2]]);
				nodes [statement->association->declarations [0]] = node;
			}
		}
	}
}

std::wstring lambda_p_kernel::cvalue::binder_name ()
{
	return std::wstring (L"cvalue");
}