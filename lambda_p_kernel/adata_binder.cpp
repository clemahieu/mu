#include "adata_binder.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/adata.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/node_list.h>

void lambda_p_kernel::adata_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::binder::data> data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->references [0]]));
		if (data.get () != nullptr)
		{
			std::wstring wide_string (data->string ());
			std::string ascii_string;
			ascii_string.resize (wide_string.size ());
			std::copy (wide_string.begin (), wide_string.end (), ascii_string.begin ());
			boost::shared_ptr <lambda_p_kernel::adata> ascii_data (new lambda_p_kernel::adata (ascii_string));
			nodes [statement->association->declarations [0]] = ascii_data;
		}
		else
		{
			unexpected_binder_type_error (0, L"data", problems);
		}
	}
}

std::wstring lambda_p_kernel::adata_binder::binder_name ()
{
	return std::wstring (L"adata_binder");
}