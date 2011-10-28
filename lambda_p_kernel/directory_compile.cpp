#include "directory_compile.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>

void lambda_p_kernel::directory_compile::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		auto directory (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->parameters [0]]));
		if (directory.get () != nullptr)
		{

		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"data"), problems);
		}
	}
}

std::wstring lambda_p_kernel::directory_compile::binder_name ()
{
	return std::wstring (L"directory_compile");
}