#include "cvalue.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/bool_c.h>
#include <lambda_p_kernel/application.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/routine.h>

void lambda_p_kernel::cvalue::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 4, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::routine> routine (boost::dynamic_pointer_cast <lambda_p_kernel::routine> (nodes [statement->association->references [0]]));
		check_binder (routine, 0, L"routine", problems);
		boost::shared_ptr <lambda_p::binder::node_list> nodes_l (boost::dynamic_pointer_cast <lambda_p::binder::node_list> (nodes [statement->association->references [1]]));
		check_binder (nodes_l, 1, L"node_list", problems);
		if (problems.errors.empty ())
		{
			lambda_p_kernel::apply apply;
			lambda_p::binder::node_list declarations;
			apply.core (*routine, *nodes_l, problems, declarations);
			if (problems.errors.empty ())
			{
				boost::shared_ptr <lambda_p_kernel::bool_c> bool_l (boost::dynamic_pointer_cast <lambda_p_kernel::bool_c> (declarations [0]));
				check_binder (bool_l, 0, L"bool_c", problems);
				if (problems.errors.empty ())
				{
					if (bool_l->value)
					{
						boost::shared_ptr <lambda_p::binder::node> node (nodes [statement->association->references [2]]);
						nodes [statement->association->declarations [0]] = node;
					}
					else
					{
						boost::shared_ptr <lambda_p::binder::node> node (nodes [statement->association->references [3]]);
						nodes [statement->association->declarations [0]] = node;
					}
				}
			}
		}
	}
}

std::wstring lambda_p_kernel::cvalue::binder_name ()
{
	return std::wstring (L"cvalue");
}