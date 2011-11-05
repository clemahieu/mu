#include "null_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>

void lambda_p_kernel::null_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	for (auto i = statement->association->declarations.begin (); i != statement->association->declarations.end (); ++i)
	{
		nodes [*i] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::null_binder);
	}
}

std::wstring lambda_p_kernel::null_binder::binder_name ()
{
	return std::wstring (L"null_binder");
}