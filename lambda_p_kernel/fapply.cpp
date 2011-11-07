#include "fapply.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/application.h>

void lambda_p_kernel::fapply::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::core::routine> routine (boost::dynamic_pointer_cast <lambda_p::core::routine> (nodes [statement->association->references [0]]));
		check_binder (routine, 0, L"routine", problems);
		boost::shared_ptr <lambda_p::binder::list> nodes_l (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [1]]));
		check_binder (nodes_l, 1, L"node_list", problems);
		if (problems.errors.empty ())
		{
			boost::shared_ptr <lambda_p_kernel::application> application (new lambda_p_kernel::application (routine, nodes_l));
			nodes [statement->association->declarations [0]] = application;
		}
	}
}

std::wstring lambda_p_kernel::fapply::binder_name ()
{
	return std::wstring (L"fapply");
}
