#include "identity.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>

void lambda_p_kernel::identity::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems)
{
	if (statement->association->parameters.size () == statement->association->results.size ())
	{
		std::vector < size_t>::iterator j (statement->association->results.begin ());
		for (std::vector < size_t>::iterator i = statement->association->parameters.begin (); i != statement->association->parameters.end (); ++i, ++j)
		{
			instances [*j] = instances [*i];
		}
	}
	else
	{
		add_error (std::wstring (L"expect same number of arguments and results"), problems);
	}
}

std::wstring lambda_p_kernel::identity::binder_name ()
{
	return std::wstring (L"identity_binder");
}