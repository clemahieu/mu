#include "package_add.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/package.h>
#include <lambda_p/binder/data.h>

void lambda_p_kernel::package_add::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 3, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::package> package (boost::dynamic_pointer_cast <lambda_p_kernel::package> (nodes [statement->association->parameters [0]]));
		if (package.get () != nullptr)
		{
			boost::shared_ptr <lambda_p::binder::data> data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->parameters [2]]));
			if (data.get () != nullptr)
			{
				package->nodes [data->string ()] = nodes [statement->association->parameters [1]];
			}
			else
			{
				unexpected_binder_type_error (2, std::wstring (L"data"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"package"), problems);
		}
	}
}

std::wstring lambda_p_kernel::package_add::binder_name ()
{
	return std::wstring (L"package_add");
}