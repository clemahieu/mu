#include "null_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>

void lambda_p_kernel::null_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems)
{
	for (std::vector < size_t>::iterator i = statement->association->results.begin (); i != statement->association->results.end (); ++i)
	{
		instances [*i] = boost::shared_ptr < lambda_p::binder::instance> (new lambda_p_kernel::null_binder);
	}
}

std::wstring lambda_p_kernel::null_binder::binder_name ()
{
	return std::wstring (L"null_binder");
}