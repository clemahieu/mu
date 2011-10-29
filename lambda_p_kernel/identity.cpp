#include "identity.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>

void lambda_p_kernel::identity::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	if (statement->association->references.size () == statement->association->declarations.size ())
	{
		auto j (statement->association->declarations.begin ());
		for (auto i = statement->association->references.begin (); i != statement->association->references.end (); ++i, ++j)
		{
			nodes [*j] = nodes [*i];
		}
	}
	else
	{
		add_error (std::wstring (L"expect same number of arguments and declarations"), problems);
	}
}

std::wstring lambda_p_kernel::identity::binder_name ()
{
	return std::wstring (L"identity_binder");
}