#include "subtract.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p_kernel/number.h>

void lambda_p_kernel::subtract::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::number> left (boost::dynamic_pointer_cast <lambda_p_kernel::number> (nodes [statement->association->references [0]]));
		check_binder (left, 0, L"number", problems);
		boost::shared_ptr <lambda_p_kernel::number> right (boost::dynamic_pointer_cast <lambda_p_kernel::number> (nodes [statement->association->references [1]]));
		check_binder (right, 1, L"number", problems);
		if (problems.errors.empty ())
		{
			boost::shared_ptr <lambda_p_kernel::number> result (new lambda_p_kernel::number (left->value - right->value));
			nodes [statement->association->declarations [0]] = result;
		}
	}
}

std::wstring lambda_p_kernel::subtract::binder_name ()
{
	return std::wstring (L"subtract");
}