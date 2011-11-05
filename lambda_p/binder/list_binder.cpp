#include "list_binder.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>

void lambda_p::binder::list_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes_a, lambda_p::errors::error_list & problems)
{
	if (statement->association->declarations.size () == 1)
	{
		boost::shared_ptr <lambda_p::binder::list> set (new lambda_p::binder::list);
		for (auto i = statement->association->references.begin (); i != statement->association->references.end (); ++i)
		{
			set->nodes.push_back (nodes_a [*i]);
		}
		nodes_a [statement->association->declarations [0]] = set;
	}
	else
	{
		add_error (std::wstring (L"expecting 1 declaration"), problems);
	}
}

std::wstring lambda_p::binder::list_binder::binder_name ()
{
	return std::wstring (L"list_binder");
}