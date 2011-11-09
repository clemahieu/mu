#include "eval.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/application.h>
#include <lambda_p_kernel/apply.h>

void lambda_p_kernel::eval::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::application> application (boost::dynamic_pointer_cast <lambda_p_kernel::application> (nodes [statement->association->references [0]]));
		check_binder (application, 0, L"application", problems);
		if (problems.errors.empty ())
		{
			lambda_p_kernel::apply apply;
			boost::shared_ptr <lambda_p::binder::list> declarations (new lambda_p::binder::list);
			apply.core (application->routine, *application->nodes, problems, *declarations);
			nodes [statement->association->declarations [0]] = declarations;
		}
	}
}

std::wstring lambda_p_kernel::eval::binder_name ()
{
	return std::wstring (L"eval");
}