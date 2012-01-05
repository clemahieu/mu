#include "not.h"

#include <lambda_p_kernel/bool_c.h>
#include <lambda_p/binder/binder_implementor.h>

void lambda_p_kernel::not::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::bool_c> value (boost::dynamic_pointer_cast <lambda_p_kernel::bool_c> (nodes [statement->association->references [0]]));
		check_binder (value, 0, L"bool_c", problems);
		if (problems.errors.empty ())
		{
			boost::shared_ptr <lambda_p_kernel::bool_c> result (new lambda_p_kernel::bool_c (!value->value));
			nodes [statement->association->declarations [0]] = result;
		}
	}
}

std::wstring lambda_p_kernel::not::binder_name ()
{
	return std::wstring (L"not");
}